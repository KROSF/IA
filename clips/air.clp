(deftemplate aeronave
    (slot compania)
    (slot origen)
    (slot destino)
    (slot velocidad (type FLOAT))
    (slot peticion (allowed-values ninguna despegue aterrizaje emergencia intercepcion informacion rumbo))
    (slot estado (allowed-values entierra ascenso crucero descenso)(default entierra))
)

(deftemplate aerodromos
    (slot identificador)
    (slot ciudad)
    (slot radar (allowed-values ON OFF))
    (slot visibilidad (type FLOAT))
    (slot viento (type FLOAT))
)

(deftemplate piloto
    (slot id_aeronave)
    (slot confirmacion (allowed-values OK SOS EXEC BY) (default BY))
)

(deftemplate vuelos
    (slot id_origen)
    (slot id_destino)
    (slot distancia (type FLOAT))
    (slot velocidad_despegue (type FLOAT)(default 240))
    (slot velocidad_crucero (type FLOAT)(default 700))
)

(defrule R1_despegue
    ?a <- (aeronave (estado entierra)(peticion despegue))
)
