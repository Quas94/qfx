/**
 * Entry point for the qfx trading application.
 *
 * Author: Michael
 */

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include "ta_libc.h"
#include "libjson.h"

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

using namespace Poco;
using namespace Poco::Net;
using namespace std;

// Edit these global variables with your own information

std::string account_id = "1234567";
std::string access_token = "ACCESS-TOKEN";
std::string instruments = "EUR_USD,USD_CAD,EUR_JPY";
std::string domain = "https://stream-fxpractice.oanda.com";

/*****************************
The domain variable should be:
For Sandbox    -> https://stream-sandbox.oanda.com
For fxPractice -> https://stream-fxpractice.oanda.com
For fxTrade    -> https://stream-fxtrade.oanda.com
******************************/

void handleStream(streambuf* stream_buffer)
{
	std::istreambuf_iterator<char> eos; // end-of-range iterator
	std::istreambuf_iterator<char> iit(stream_buffer); // stream iterator
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

int main()
{
	try {
		// prepare session
		URI uri(domain + std::string("/v1/prices?accountId=") + account_id + std::string("&instruments=") + instruments);

		HTTPClientSession session(uri.getHost(), uri.getPort());
		session.setKeepAlive(true);

		// prepare path
		string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		// send request
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		req.set("Authorization", std::string("Bearer ") + access_token);
		session.sendRequest(req);

		// get response
		HTTPResponse res;
		istream& rs = session.receiveResponse(res);

		// handle response
		ostringstream out_string_stream;
		handleStream(rs.rdbuf());
	}
	catch (const Exception &e)
	{
		cerr << e.displayText() << endl;
	}
}
