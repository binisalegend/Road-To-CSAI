test = {
  'name': 'Recursion',
  'points': 0,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> def f(a, b):
          ...     if a > b:
          ...         return f(a - 3, 2 * b)
          ...     elif a < b:
          ...         return f(b // 2, a)
          ...     else:
          ...         return b
          >>> f(2, 2)
          73a9752b0761167119f7a8667ed17719
          # locked
          >>> f(7, 4)
          ad741b000d1cc7ef3beaaf650d8f371b
          # locked
          >>> f(2, 28)
          11f2dd23b3fd248f63abf27f5ba01f68
          # locked
          >>> f(-1, -3)
          47fe0628cbfd93cd06420a3a6865a28b
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
