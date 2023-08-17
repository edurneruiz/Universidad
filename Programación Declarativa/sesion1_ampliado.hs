--Edurne Ruiz Huguet

--ejercicio 1
type Coordenada = 0 | 1 | 2 | 3
type Punto = (Coordenada,Coordenada)
type Direccion = arriba | abajo | izquierda | derecha deriving Eq, Ord, Show

--mueve p m devuelve el punto al que se mueve el punto p al aplicarle el movimiento m.mueve::Punto -> Direccion -> Puntomueve (f, c) arriba = (min 100 f+1, c)
mueve (f, c) abajo = (max 0 f-1, c)
mueve (f, c) izquierda = (f, max 0 c-1)
mueve (f, c) derecha = (f, min 100 c+1)

--destino p ms devuelve el punto final al que se llega desde el punto p, al aplicar los movimientos de la lista finita ms.
destino:: Punto -> [Direccion] -> Punto

destino p m:ms = foldl (mueve p) ms m

--trayectoria p ms devuelve la lista de puntos por los que se pasa al aplicar la lista de movimientos finita ms al punto del plano p
--trayectoria :: Punto -> [Direccion] -> [Punto]

--trayectoria p ms = 