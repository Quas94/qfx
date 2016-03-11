# qfx

Disclaimer: The main role fulfilled by this trading strategy is an educational one - in order to learn more about foreign exchange, technical analysis, developing in C++ and testing out a (potentially completely fruitless) trading idea.

# Strategy Overview

The general idea of this strategy is simple:
- Pick a currency, and check through all of its common pairs with a range of technical analysis tools.
- Increase or decrease its score based on whether it is expected to rise or fall in the pairs for each tool.
- Do this for all major currencies and their common pairs.
- Make trades by pairing the highest scoring currencies with the lowest, and trade those pairs accordingly. eg. If AUD had the highest score from our TA aggregate analysis and JPY had the lowest, open a trade to go long on AUD/JPY.

# Possible Pitfalls

- One currency could be projected to rise greatly from a pairing, when in reality it's solely due to the fall of the other side of the pair. This would need to be accounted for.
