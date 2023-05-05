import time
from tabulate import tabulate

def slowDiscLog(base, ans, mod):
  """
  same process as...
  for i in range(mod-1):
    if(pow(base, i, mod) == ans):
      return i
  """
  tempExp = 1
  tempAns = 1
  while(tempExp < mod):
    tempAns = pow(base, tempExp, mod)
    if (tempAns == ans):
      return tempExp
    tempExp += 1
    
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
    slowResult = slowDiscLog(bases[i], answers[i], mods[i])
    timeEnd = time.time()
    timeElapsed = timeEnd - timeStart
    exponents[i] = slowResult
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