(deftemplate aeronave 
	(slot id_aeronave)
	(slot company )
	(slot origen)
	(slot destino)
	(slot vel_actual)
	(slot peticion (allowed-values Ninguna Despegue Aterrizaje Emergencia Interceptacion Informacion Rumbo))
	(slot estado (allowed-values enTierra Ascenso Crucero Descenso)(default enTierra))
)

(deftemplate aerodromo
	(slot id_aerodromo)
	(slot city)
	(slot radar (allowed-values ON OFF)
	(slot radiovisi)
	(slot vviento)
)

(deftemplate piloto 
	(slot id_aeronave)
	(slot estado (allowed-values OK SOS Ejecutando Standby) (default Standby))
)

(deftemplate vuelo 
	(slot id_aerodromodest)
	(slot id_aerodromosali)
	(slot distancia)
	(slot velocidad_despegue (default 240))
	(slot velocidad_crucero (default 700))
)

(deffunction tiempo_vuelo (?d ?v)
    (bind ?r (/ ?d ?v))
    (return ?r)
)

(defrule R1_Despegar
    (declare(salience 20))
    ?f1<-(aeronave (estado enTierra)(peticion Despegue)(id_aeronave ?ida)(origen ?oi)(vel_actul ?va)(company ?comp))
    ?f2<-(piloto (id_aeronave ?ida)(estado OK))
    (aerodromo (id_aerodromo ?ae)(radar ON)(city ?oi)(radiovisi ?rv)(vviento ?vv))
    (vuelo (id_aerodromosali ?ae)(velocidad_despegue ?vd))
    (test > ?rv 5)
    (test < ?vv 75)
    =>
    (modify ?f2(estado Ejecutando))
    (modify ?f1(estado Ascenso)(vel_actual ?vd )(peticion Ninguna))
    (printout t "El vuelo " ?ida " de la compania " ?comp " va a realizar la accion despegue desde el aerodromo " ?idaerodromo " de " ?ciudadorigen " con destino " ?ciudaddest crlf)
)

(defrule R2_Excepcion 
    (declare(salience 21))
    (not (piloto (id_aeronave ?id)))
    ?f1<-(aeronave (id_aeronave ?id)(peticion Despegue)(origen ?oi))
    (aerodromo (city ?oi)(id_aerodromo ?ae))
    (vuelo (id_aerodromosali ?ae))	
    =>
    (modify ?f1(peticion Emergencia))
    (printout t " NO piloto == aeronave estrellada" crlf)
)

(defrule R3_Crucero
    ?f1<-(aeronave (id_aeronave ?ida)(v_actual ?vdespegue)(peticion Ninguna)(eActual Ascenso))
    ?f2<-(piloto (id_aeronave ?ida)(estado Ejecutando))
    (vuelo (distancia ?dist)(v_despegue ?vdespegue)(v_crucero ?vcrucero))
    =>
    (modify ?f1 (v_actual ?vcrucero) (eActual Crucero))
    (modify ?f2 (estado Stand-by))
    (printout t "El despegue se ha realizado correctamente, tiempo estimado de vuelo: " (tiempo_vuelo ?dist ?vcrucero) ". Disfruten del vuelo." crlf)
)
