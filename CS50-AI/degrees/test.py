from pomegranate import *

start = DiscreteDistribution({'Rainy': 0.5, 'Sunny': 0.5})

transitions = ConditionalProbabilityTable([
    ['Rainy', 'Rainy', 0.8],
    ['Rainy', 'Sunny', 0.2],
    ['Sunny', 'Rainy', 0.4],
    ['Sunny', 'Sunny', 0.6]
], [start])

model = MarkovChain([start, transitions])

print(model.sample(10))
    