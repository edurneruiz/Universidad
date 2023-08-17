--Edurne Ruiz Huguet

--EJERCICIO 1

-- Define un tipo Punto para representar coordenadas con filas y columnas numeradas de 0 a 100. 
-- Define un tipo enumerado Direccion con cuatro valores que representen movimientos
type Punto = (Int, Int)
data Direccion = Quieto | Arriba | Abajo | Izquierda | Derecha deriving (Eq, Ord, Show)

-- mueve p m devuelve el punto al que se mueve el punto p al aplicarle el movimiento m
mueve :: Punto -> Direccion -> Punto
mueve (f, c) Quieto = (f, c)
mueve (f, c) Arriba = if f == 100 then (100, c) else (f+1, c)
mueve (f, c) Abajo = if f == 0 then (0, c) else (f-1, c)
mueve (f, c) Izquierda = if c == 0 then (f, 0) else (f, c-1)
mueve (f, c) Derecha = if c == 100 then (f, 100) else (f, c+1)

-- destino p ms devuelve el punto final al que se llega desde el punto p, al aplicar sucesivamente los movimientos de la lista de movimientos finita ms.
destino :: Punto -> [Direccion] -> Punto
destino p ms = foldl mueve p ms

-- trayectoria p ms devuelve la lista de puntos por los que se pasa al aplicar la lista de movimientos finita ms al punto del plano p
trayectoria :: Punto -> [Direccion] -> [Punto]
trayectoria p ms = foldl (\x y -> [x] ++ [mueve (last x) y]) [p] ms

--EJERCICIO 2

data Nat = Cero | Suc Nat deriving (Eq, Ord)

-- Define operadores infijos para calcular la suma y el producto de elementos de Nat.

infixr 6 +++
(+++):: Nat -> Nat -> Nat
Cero +++ n = n
(Suc m) +++ n = Suc(m +++ n)

infixr 6 ***
(***):: Nat -> Nat -> Nat
n *** Cero = Cero
n *** (Suc m) = (n *** m) +++ n

-- Define natToInt que convierta una expresion de tipo Nat en su correspondiente valor numérico en el tipo Int.
natToInt :: Num a => Nat -> a

natToInt Cero = 0
natToInt (Suc n) = 1 + natToInt n

-- Declarar Nat como instancia de Show
instance Show Nat where
	show n = show $ natToInt n

--EJERCICIO 3

data Complejo = C Float Float

instance Eq Complejo where
	C a b == C c d = (a == c) && (b == d)

instance Show Complejo where
	show (C a b)
		| b == 0 = show a
		| b < 0 = show a ++ show b ++ "i"
		| b > 0 = show a ++ "+" ++ show b ++ "i"

instance Num Complejo where
	(C a b) + (C c d) = C (a+c) (b+d)
	(C a b) - (C c d) = C (a-c) (b-d)
	(C a b) * (C c d) = C (a*c-b*d) (a*d+b*c)

instance Fractional Complejo where
	(C a b) / (C c d) = (C ((a*c+b*d)/(c*c+d*d)) ((b*c - a*d)/(c*c+d*d)) )


--EJERCICIO 4

--Define una clase de tipos Medible que disponga de un método medida::a -> Int que se pueda aplicar a cada tipo a de dicha clase. 

class Medible m where
	medida:: m -> Int

instance Medible Bool where
	medida False = 0
	medida True = 1

instance Medible a => Medible [a] where
	medida [] = 0
	medida (x:xs) = medida x + medida xs
