-- EDURNE RUIZ HUGUET

getInt :: IO Int
getInt = do line <- getLine
            return (read line::Int)

getFloat :: IO Float
getFloat = do line <- getLine
              return (read line::Float)

-- Ejercicio 1

adivina:: Int -> IO()
adivina n = do
            putStr "Introduce un numero entero: "
            m <- getInt
            if m > n then do 
                               putStr "El numero introducido es mayor al deseado"
                               adivina n
            else if m < n then do
                                    putStr "El numero introducido es menor al deseado"
                                    adivina n
            else putStr "Adivinaste!\n"

-- Ejercicio 2
type Fila = [Float]
type Matriz = [Fila]

-- a)                          

readMatriz ::Int->Int->Int->Matriz-> IO Matriz
readMatriz filas columnas i m = if i < filas then do
                                           putStr ("Fila"++ show i ++":")
                                           fila <- getFila columnas 0 []
                                           readMatriz filas columnas (i+1) (m++[fila])
                         else return m


getFila::Int->Int-> Fila ->IO Fila
getFila columnas j fila = if j < columnas then do
                                               elem <- getFloat
                                               getFila columnas (j+1) (fila++[elem])
                          else return fila
                          

getMatriz::IO Matriz
getMatriz = do 
            putStr "Inserta el numero de filas"
            filas <- getInt
            putStr "Inserta el numero de columnas"
            columnas <- getInt
            readMatriz filas columnas 0 []


-- b)
dibujaFila :: Fila -> IO ()
dibujaFila [] = putStrLn ""
dibujaFila (x:xs) = do putStr(show x ++ " ")
                       dibujaFila xs

dibujaMatriz :: Matriz -> IO ()
dibujaMatriz [] = putStr ""
dibujaMatriz (f:fs) = do dibujaFila f
                         dibujaMatriz fs

-- Ejercicio 3
formateaLinea:: Int -> String -> String 
formateaLinea n linea = concat $ map (espacio ++) (words linea) ++ ["\n"]
   where m = sum $ map length (words linea)
         espacio = if m >= n then " "
         else last (take ((n-m) `div` (length (words linea)))(iterate (" "++)" "))


formatea:: String -> String -> Int -> IO()
formatea fileIn fileOut n = do
                            file <- readFile fileIn
                            let lineas = lines file
                            let array = concat $ map (formateaLinea n) lineas
                            writeFile fileOut array