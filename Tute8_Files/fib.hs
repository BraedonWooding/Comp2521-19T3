module Fib where

import System.Environment
import System.Exit
import Data.Function

getIntArg :: IO Int
getIntArg = fmap (read . head) getArgs

main = do
    n <- getIntArg
    print $ fib n

fib :: Int -> Int
fib = (map fib_memo [0 ..] !!)
    where fib_memo 0 = 1
          fib_memo 1 = 1
          fib_memo n = fib (n - 2) + fib (n - 1)

