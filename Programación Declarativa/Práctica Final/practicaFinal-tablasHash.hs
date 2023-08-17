--EDURNE RUIZ HUGUET
--Escribir un programa en Haskell que implemente una serie de funciones para manejar un diccionario espa�ol-ingl�s.
--Las entradas del diccionario ser�n pares de palabras. Donde la segunda componente del par representa la traducci�n 
--de la primera. El diccionario se guardar� en una tabla hash, que habr� que inicializar a partir de un fichero de 
--texto dado, que contiene los pares de palabras para poder ser usado posteriormente con el fin de traducir frases.

--He escrito esta funci�n principal, que inicializa la tabla Hash (aunque no la muestra), pregunta por las palabras 
--que se desean traducir, calcula su longitud media y devuelve su traducci�n al ingl�s (en caso de que est�n en la tabla)
--o un mensaje de que no se han podido encontrar.

main :: IO ()
main = do
         (H h) <- inicializacion
         esp <- leerPalabras
         longitudMediaPalabras esp
         let ing = traduccionPalabras h esp
         mostrar esp ing
         return ()

--He escrito esta funci�n para mostrar el diccionario reci�n inicializado con los valores del fichero.

mostrarDicc :: IO ()
mostrarDicc = do 
                (H h) <- inicializacion
                putStrLn "Nuestro diccionario es el siguiente: "
                print (H h)

--EJERCICIO 1: Definici�n de una estructura de datos de nombre Hash para representar una tabla hash. 

--Definimos el tipo Trad (traducci�n), un par clave-valor tq la clave es la palabra en espa�ol y el valor su traducci�n al ingl�s,
--          el tipo Fila, que ser� una lista de traducciones (representa una fila de la tabla Hash a crear),
--          el tipo MyHash, una lista de Filas, es decir, la tabla propiamente dicha.
--La tabla Hash la representamos como una estructura de datos con constructora de clase H y tipo MyHash.

type Trad = (String, String)
type Fila = [Trad]
type MyHash = [Fila]

data Hash = H MyHash

--EJERCICIO 2: Declaraci�n del tipo Hash como instancia de la clase Show, mediante redefinici�n del m�todo show.

instance Show Hash where
      show (H h) = showHash h 0

--Funci�n recursiva que va mostrando cada fila de la forma |j| -> ("",""), ...
showHash :: MyHash -> Int -> String
showHash [] _ = ""
showHash (f:fs) j = "|" ++ show j ++ "|->" ++ fila ++ resto
                    where fila = showFila f
                          resto = showHash fs (j+1)

--Funci�n recursiva auxiliar para mostrar cada traducci�n de una misma Fila.
showFila :: Fila -> String
showFila [] = "\n"
showFila (t:ts) = show t ++ ", " ++ showFila ts

--EJERCICIO 3: Definici�n de la funci�n hash. El �ndice tiene solo 10 valores distintos.
--Definimos funci�n auxiliar que no depende del n�mero de valores distintos.

fhashN :: Int -> String -> Int
fhashN n x = mod (sum (map fromEnum x)) n

fhash :: String -> Int
fhash = fhashN 10

--EJERCICIO 4: Inicializaci�n del diccionario: rellena la tabla hash a partir del fichero de texto dado datos.txt.

inicializacion :: IO Hash
inicializacion = do
                   let v = inicializarHash []
                   h <- introducirFichero v
                   return (H h)

--Inicializamos la tabla Hash vac�a de tama�o n, y luego particularizamos a la de tama�o 10.

inicializarHashN :: Int -> MyHash -> MyHash
inicializarHashN 0 h = h
inicializarHashN n h = [[]] ++ inicializarHashN (n-1) h

inicializarHash :: MyHash -> MyHash
inicializarHash = inicializarHashN 10

--Funciones para introducir los pares (espa�ol, ingles) de un fichero dado. Luego particularizamos al fichero de esta pr�ctica.

introducirFicheroF :: String -> MyHash -> IO MyHash
introducirFicheroF fileIn h = do
                                file <- readFile fileIn
                                let lineas = lines file
                                return (rellenarHash h lineas)

introducirFichero :: MyHash -> IO MyHash
introducirFichero = introducirFicheroF "datos.txt"

rellenarHash :: MyHash -> [String] -> MyHash
rellenarHash h [] = h
rellenarHash h (l:ls) = rellenarHash h' ls
                        where h' = annadirTrad i h (esp, ing)
                              (esp, ing) = ((words l) !! 0, (words l) !! 1)
                              i = fhash esp

--A�adimos la traducci�n t en su correspondiente fila i de la tabla Hash h. Para ello, dividimos la tabla en tres:
--xs, las primeras filas que no debemos modificar;
--y, la fila en la que vamos a insertar la traducci�n;
--zs, las �ltimas filas no modificadas

annadirTrad :: Int -> MyHash -> Trad -> MyHash
annadirTrad i h t = xs ++ [y ++ [t]] ++ zs
                    where (xs, y, zs) = splitAt' i h

--Definimos la funci�n auxiliar (gen�rica) splitAt' para que haga dicha partici�n en la posici�n i que deseemos.

splitAt' :: Int -> [a] -> ([a], a, [a])
splitAt' i l = (xs, head ys, tail ys)
               where (xs, ys) = splitAt i l 

--EJERCICIO 5: Lectura de varias palabras a traducir introducidas por el teclado.

leerPalabras :: IO [String]
leerPalabras = do
                 putStr "Introduce las palabras a traducir (separadas por espacios): "
                 entrada <- getLine
                 return (words entrada)

-- EJERCICIO 6: C�lculo de la longitud media de las palabras introducidas.

longitudMediaPalabras :: [String] -> IO ()
longitudMediaPalabras p = putStrLn ("La longitud media de las palabras introducidas es " ++ show l)
                          where l = longitudMedia p

longitudMedia :: Fractional a => [String] -> a
longitudMedia [] = 0
longitudMedia palabras = (fromIntegral (sum [length p | p <- palabras])) / (fromIntegral (length palabras))

-- EJERCICIO 7: B�squeda en el diccionario de la traducci�n de las palabras introducidas.

traduccion :: MyHash -> IO [String]
traduccion h = do 
                 p <- leerPalabras
                 return (traduccionPalabras h p)

--Va intentando traducir de una en una las palabras solicitadas y a�adi�ndolas a la lista de salida. 

traduccionPalabras :: MyHash -> [String] -> [String]
traduccionPalabras _ [] = []
traduccionPalabras h (p:ps) = [traducirPalabra h p] ++ traduccionPalabras h ps

--Calcula en qu� fila deber�a estar la palabra solicitada y va a buscarla.

traducirPalabra :: MyHash -> String -> String
traducirPalabra h p = buscarPalabra (h !! i) p
                      where i = fhash p				

--Recorre la fila d�nde deber�a encontrarse la palabra solicitada seg�n la funci�n hash.

buscarPalabra :: Fila -> String -> String
buscarPalabra [] _ = " no aparece en el diccionario."
buscarPalabra (t:ts) p
             | p == fst t = " es " ++ snd t ++ ". "
             | otherwise = buscarPalabra ts p

--EJERCICIO 8: Muestra en pantalla la traducci�n de las palabras en el orden en el que se introdujeron o un mensaje de error.

mostrar :: [String] -> [String] -> IO ()
mostrar esp ing = mostrarTraducciones (zip esp ing)

mostrarTraducciones :: [Trad] -> IO ()
mostrarTraducciones [] = putStrLn ""
mostrarTraducciones (t:ts) = do 
                               putStrLn ("La traduccion de " ++ fst t ++ snd t)
                               mostrarTraducciones ts