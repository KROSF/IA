(reset)
(clear)

(deftemplate valvula
    (slot nombre)
    (slot temperatura_interna (default 0))
    (slot temperatura_externa (default 0))
    (slot presion (default 0))
    (slot estado (default cerrada)(allowed-values abierta cerrada))
)

(deffacts iniciales
    (valvula (nombre ENTRADA)(temperatura_interna 101)(temperatura_externa 35)(presion 1))
    (valvula (nombre SALIDA)(temperatura_interna 101)(temperatura_externa 155)(presion 5))
    (valvula (nombre PASILLO1)(temperatura_interna 99)(temperatura_externa 37))
)

(deffunction incrementar (?presion ?temperatura)
    (while (> ?temperatura 35)
        (bind ?temperatura (- ?temperatura 5))
        (bind ?presion (+ ?presion 1))
    )
    (return ?presion)
)

(deffunction decrementar (?temp_1 ?temp_2)
    (if (> ?temp_2 ?temp_1) then
     (bind ?temp_2 (- ?temp_2 ?temp_1))
    )
    (return ?temp_2)
)

(defrule R1
    ?v <- (valvula (nombre ?nom)(presion ?p)(estado abierta))
    (test (eq ?p 5))
    =>
    (modify ?v (presion 0)(estado cerrada))
    (printout t "La valvula " ?nom " se ha cerrado" crlf)
)

(defrule R2
    ?v <- (valvula (nombre ?nom)(presion ?p)(estado cerrada)(temperatura_interna ?temp))
    (test (> ?temp 35))
    =>
    (bind ?p (incrementar ?temp ?p))
    (modify ?v (estado abierta)(presion ?p)(temperatura_interna 35))
    (printout t "La valvula " ?nom " a decrementado su temperatura" crlf)
)

(defrule R3
    ?v1 <- (valvula (nombre ?nom1)(temperatura_interna ?tempi1)(temperatura_externa ?tempe1)(estado ?est1))
    ?v2 <- (valvula (nombre ?nom2)(temperatura_interna ?tempi2)(temperatura_externa ?tempe2)(estado ?est2))
    (test (= ?tempe1 ?tempe2))
    (test (< ?tempi2 ?tempe2))
    =>
    (modify ?v1 (estado abierta))
    (modify ?v2 (estado abierta))
    (bind ?tempe2 (decrementar ?tempi1 ?tempe2))
)
