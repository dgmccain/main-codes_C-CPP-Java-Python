import time
import math
from tabulate import tabulate

def sqrtDiscLog(base, ans, mod):
  # Can use N = math.ceil(math.sqrt(mod-1)) instead
  modSqrt = int(math.sqrt(mod)+1)

  # Hashtable... base^i % mod: i
  hTable = {pow(base, i, mod): i for i in range(modSqrt)}

  # Fermat's Little Theorem... base^(sqrt(mod)*mod-2) % mod
  fermLit = pow(base, modSqrt*(mod-2), mod)

  # Search through table to find respective exponent
  for j in range(modSqrt):
    y = (ans*pow(fermLit, j, mod)) % mod
    if y in hTable:
      return j*modSqrt + hTable[y]

  # Solution not found
  return -1

def mainProgram():
  numTests = 6
  # Fixed tests are listed below
  bases = [ 5, 5, 211523205, 75853221, 1003708272, 1204331962 ]
  answers = [ 123456, 87123456, 1036204576, 96317213, 1820444653, 505493879 ]
  mods = [ 1000000007, 1000000007, 1999999973, 1450001227, 1910003723, 1910003723 ]

  # Stored for output later
  exponents = [0] * numTests
  runTimes = [0] * numTests

  # Process for finding exponent
  for i in range(numTests):
    timeStart = time.time()
    fastResult = sqrtDiscLog(bases[i], answers[i], mods[i])
    timeEnd = time.time()
    timeElapsed = timeEnd - timeStart
    exponents[i] = fastResult
    """
    dataframe table has limit of 6 digits for runTime.
    Otherwise: 'runTimes[i] = round(timeElapsed, 5)'
    could be used to round runTime to nearest hundred-
    thousandth. Also, the table ignores outputting the
    last decimal place if it equals zero
    """
    runTimes[i] = timeElapsed

  # Output
  table = [""] * (numTests+1)
  table[0] = ['Base', 'Ans', 'Mod', 'X', 'Time']
  for i in range(numTests):
    table[i+1] = [bases[i], answers[i], mods[i], exponents[i], runTimes[i]]
  print(tabulate(table, headers='firstrow', tablefmt='fancy_grid'))

# Execute program
mainProgram()