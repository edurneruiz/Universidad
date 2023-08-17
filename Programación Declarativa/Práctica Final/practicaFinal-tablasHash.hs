--EDURNE RUIZ HUGUET
--Escribir un programa en Haskell que implemente una serie de funciones para manejar un diccionario español-inglés.
--Las entradas del diccionario serán pares de palabras. Donde la segunda componente del par representa la traducción 
--de la primera. El diccionario se guardará en una tabla hash, que habrá que inicializar a partir de un fichero de 
--texto dado, que contiene los pares de palabras para poder ser usado posteriormente con el fin de traducir frases.

--He escrito esta función principal, que inicializa la tabla Hash (aunque no la muestra), pregunta por las palabras 
--que se desean traducir, calcula su longitud media y devuelve su traducción al inglés (en caso de que estén en la tabla)
--o un mensaje de que no se han podido encontrar.

main :: IO ()
main = do
         (H h) <- inicializacion
         esp <- leerPalabras
         longitudMediaPalabras esp
         let ing = traduccionPalabras h esp
         mostrar esp ing
         return ()

--He escrito esta función para mostrar el diccionario recién inicializado con los valores del fichero.

mostrarDicc :: IO ()
mostrarDicc = do 
                (H h) <- inicializacion
                putStrLn "Nuestro diccionario es el siguiente: "
                print (H h)

--EJERCICIO 1: Definición de una estructura de datos de nombre Hash para representar una tabla hash. 

--Definimos el tipo Trad (traducción), un par clave-valor tq la clave es la palabra en español y el valor su traducción al inglés,
--          el tipo Fila, que será una lista de traducciones (representa una fila de la tabla Hash a crear),
--          el tipo MyHash, una lista de Filas, es decir, la tabla propiamente dicha.
--La tabla Hash la representamos como una estructura de datos con constructora de clase H y tipo MyHash.

type Trad = (String, String)
type Fila = [Trad]
type MyHash = [Fila]

data Hash = H MyHash

--EJERCICIO 2: Declaración del tipo Hash como instancia de la clase Show, mediante redefinición del método show.

instance Show Hash where
      show (H h) = showHash h 0

--Función recursiva que va mostrando cada fila de la forma |j| -> ("",""), ...
showHash :: MyHash -> Int -> String
showHash [] _ = ""
showHash (f:fs) j = "|" ++ show j ++ "|->" ++ fila ++ resto
                    where fila = showFila f
                          resto = showHash fs (j+1)

--Función recursiva auxiliar para mostrar cada traducción de una misma Fila.
showFila :: Fila -> String
showFila [] = "\n"
showFila (t:ts) = show t ++ ", " ++ showFila ts

--EJERCICIO 3: Definición de la función hash. El índice tiene solo 10 valores distintos.
--Definimos función auxiliar que no depende del número de valores distintos.

fhashN :: Int -> String -> Int
fhashN n x = mod (sum (map fromEnum x)) n

fhash :: String -> Int
fhash = fhashN 10

--EJERCICIO 4: Inicialización del diccionario: rellena la tabla hash a partir del fichero de texto dado datos.txt.

inicializacion :: IO Hash
inicializacion = do
                   let v = inicializarHash []
                   h <- introducirFichero v
                   return (H h)

--Inicializamos la tabla Hash vacía de tamaño n, y luego particularizamos a la de tamaño 10.

inicializarHashN :: Int -> MyHash -> MyHash
inicializarHashN 0 h = h
inicializarHashN n h = [[]] ++ inicializarHashN (n-1) h

inicializarHash :: MyHash -> MyHash
inicializarHash = inicializarHashN 10

--Funciones para introducir los pares (español, ingles) de un fichero dado. Luego particularizamos al fichero de esta práctica.

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

--Añadimos la traducción t en su correspondiente fila i de la tabla Hash h. Para ello, dividimos la tabla en tres:
--xs, las primeras filas que no debemos modificar;
--y, la fila en la que vamos a insertar la traducción;
--zs, las últimas filas no modificadas

annadirTrad :: Int -> MyHash -> Trad -> MyHash
annadirTrad i h t = xs ++ [y ++ [t]] ++ zs
                    where (xs, y, zs) = splitAt' i h

--Definimos la función auxiliar (genérica) splitAt' para que haga dicha partición en la posición i que deseemos.

splitAt' :: Int -> [a] -> ([a], a, [a])
splitAt' i l = (xs, head ys, tail ys)
               where (xs, ys) = splitAt i l 

--EJERCICIO 5: Lectura de varias palabras a traducir introducidas por el teclado.

leerPalabras :: IO [String]
leerPalabras = do
                 putStr "Introduce las palabras a traducir (separadas por espacios): "
                 entrada <- getLine
                 return (words entrada)

-- EJERCICIO 6: Cálculo de la longitud media de las palabras introducidas.

longitudMediaPalabras :: [String] -> IO ()
longitudMediaPalabras p = putStrLn ("La longitud media de las palabras introducidas es " ++ show l)
                          where l = longitudMedia p

longitudMedia :: Fractional a => [String] -> a
longitudMedia [] = 0
longitudMedia palabras = (fromIntegral (sum [length p | p <- palabras])) / (fromIntegral (length palabras))

-- EJERCICIO 7: Búsqueda en el diccionario de la traducción de las palabras introducidas.

traduccion :: MyHash -> IO [String]
traduccion h = do 
                 p <- leerPalabras
                 return (traduccionPalabras h p)

--Va intentando traducir de una en una las palabras solicitadas y añadiéndolas a la lista de salida. 

traduccionPalabras :: MyHash -> [String] -> [String]
traduccionPalabras _ [] = []
traduccionPalabras h (p:ps) = [traducirPalabra h p] ++ traduccionPalabras h ps

--Calcula en qué fila debería estar la palabra solicitada y va a buscarla.

traducirPalabra :: MyHash -> String -> String
traducirPalabra h p = buscarPalabra (h !! i) p
                      where i = fhash p				

--Recorre la fila dónde debería encontrarse la palabra solicitada según la función hash.

buscarPalabra :: Fila -> String -> String
buscarPalabra [] _ = " no aparece en el diccionario."
buscarPalabra (t:ts) p
             | p == fst t = " es " ++ snd t ++ ". "
             | otherwise = buscarPalabra ts p

--EJERCICIO 8: Muestra en pantalla la traducción de las palabras en el orden en el que se introdujeron o un mensaje de error.

mostrar :: [String] -> [String] -> IO ()
mostrar esp ing = mostrarTraducciones (zip esp ing)

mostrarTraducciones :: [Trad] -> IO ()
mostrarTraducciones [] = putStrLn ""
mostrarTraducciones (t:ts) = do 
                               putStrLn ("La traduccion de " ++ fst t ++ snd t)
                               mostrarTraducciones ts