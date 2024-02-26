test = {
  'name': 'Self-Reference',
  'points': 0,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> def crust():
          ...   print("70km")
          ...   def mantle():
          ...       print("2900km")
          ...       def core():
          ...           print("5300km")
          ...           return mantle()
          ...       return core
          ...   return mantle
          >>> drill = crust
          >>> drill = drill()
          d6e6126b560b4b762500dc896cd7024b
          # locked
          >>> drill = drill()
          d1d999d91bf5840463d84cb0990f5093
          # locked
          >>> drill = drill()
          5b6a75898f254441a636f61686576acb
          d1d999d91bf5840463d84cb0990f5093
          # locked
          >>> drill()
          5b6a75898f254441a636f61686576acb
          d1d999d91bf5840463d84cb0990f5093
          409d225c8d71bdae383b166e754adf05
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': False,
      'type': 'wwpp'
    }
  ]
}
