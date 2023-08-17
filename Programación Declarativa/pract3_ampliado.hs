--Edurne Ruiz y Aitor Esteban

--ejercicio 1

lastM :: Ord a => [a] -> a
lastM (x:xs) = foldl (\x -> \y -> y) x xs

reverseM :: Ord a=>  [a] -> [a]
reverseM = foldr (\x y -> y ++ [x]) []

allM :: Eq a => (a-> Bool) -> [a] -> Bool 
allM p = foldr (\x y-> (p x) && y) True 

minimumM :: Ord a => [a] -> a
minimumM (x:xs) = foldr (\x y -> if (x < y) then x else y) x xs 

mapM:: (a->b)->[a]->[b]
mapM f [] = []
mapM f (x:xs) = foldr (\x xs -> (f x):xs) [] xs

filterM::(a->Bool) -> [a] -> [a]
filterM p [] = []
filterM p (x:xs) = foldr (\x xs -> if p x then x:xs else xs) [] xs

takeWhileM:: (a->Bool)->[a]->[a]
takeWhileM p = foldr (\x xs -> if p x then x:xs else []) []

--ejercicio 2
enterosHasta100 = foldl (\xs x -> xs ++ [x,-x]) [] [1..100]

-- ejercicio 3
listaInfinita = [(x,y) | z <- [0..], x <- [0..z], y <- [0..z], x + y == z]

--ejercicio 4
--a
sufijos :: [a] -> [[a]]
sufijos xs = [drop n xs | n <- [0..length xs] ]

sublistas :: [a] -> [[a]]
sublistas xs = [] : [ take (n-k) (drop k xs) | n <- [l, l-1..0], k <- [n-1, n-2..0]] where l = length xs 

permuta :: Eq a => [a] -> [[a]]
permuta [] = [[]]
permuta xs = [ y:ys | y <- xs, ys <- (permuta $ filter (\z-> z/= y) xs) ]

--sumandos :: (Eq a, Num a, Enum a) => a -> [[a]]
--sumandos n = [ x | x <- [1..n], foldr (+) 0 [x] == n ]