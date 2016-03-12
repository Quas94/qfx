/**
 * Entry point to the trading strategy.
 *
 * Author: Quasar
 * Date:   11/3/16
 */

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

#include "Config.hpp"

using namespace Poco;
using namespace Poco::Net;
using namespace std;

// Edit these global variables with your own information

string instruments = "EUR_USD,USD_CAD,EUR_JPY";
string domain = "https://stream-fxpractice.oanda.com";

/*****************************
The domain variable should be:
For Sandbox    -> https://stream-sandbox.oanda.com
For fxPractice -> https://stream-fxpractice.oanda.com
For fxTrade    -> https://stream-fxtrade.oanda.com
******************************/

void handleStream(streambuf* stream_buffer) {
	istreambuf_iterator<char> eos; // end-of-range iterator
	istreambuf_iterator<char> iit(stream_buffer); // stream iterator
	string str;

	while (iit != eos) {
		ostringstream oss;
		while (*iit != '\n') {
			oss << *iit++;
		}

		//print the tick 
		cout << oss.str() << endl;

		*iit++;
	}
}

int main() {
	// load config file
	string accountId;
	string apiKey;
	try {
		Qfx::Config conf("oanda.conf");
		accountId = conf[Qfx::Config::ACCOUNT_ID];
		apiKey = conf[Qfx::Config::API_KEY];
	} catch (const Qfx::ConfigException& e) {
		cout << "Exception encountered:" << endl;
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}

	// connect to Oanda API and accept input data
	try {
		const Context::Ptr context = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

		// prepare session
		URI uri(domain + "/v1/prices?accountId=" + accountId + "&instruments=" + instruments);

		HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
		session.setKeepAlive(true);

		// prepare path
		string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		// send request
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		req.set("Authorization", string("Bearer ") + apiKey);
		session.sendRequest(req);

		// get response
		HTTPResponse res;
		istream& rs = session.receiveResponse(res);

		// handle response
		ostringstream out_string_stream;
		handleStream(rs.rdbuf());
	} catch (const Exception &e) {
		cerr << e.displayText() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
