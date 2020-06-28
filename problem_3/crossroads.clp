(deftemplate via
   (slot identificador)
   (slot descripcion)
   (slot vehiculo (type INTEGER)))

(deftemplate semaforo
   (slot identificador)
   (slot via)
   (slot estado (allowed-values verde rojo)))

(deftemplate sensor
   (slot identificador)
   (slot semaforo)
   (slot estado (allowed-values activado desactivado) (default desactivado))
   (slot vehiculo))

(deftemplate vehiculo
   (slot matricula)
   (slot tipo (allowed-values automovil camion motocicleta bicicleta))
   (slot via)
   (slot accion (allowed-values ausente llegando esperando cruzando realizado) (default ausente)))

(deffacts hechos_iniciales
   ;; Vias
   (via (identificador via_1) (descripcion primera))
   (via (identificador via_2) (descripcion segunda))
   ;; Vehiculos
   (vehiculo (matricula 1234ASD) (tipo automovil) (via via_1))
   (vehiculo (matricula 1234ABC) (tipo camion) (via via_1))
   (vehiculo (matricula 1234XYZ) (tipo motocicleta) (via via_2))
   (vehiculo (matricula 1234IJK) (tipo bicicleta) (via via_2))
   ;; Semaforos
   (semaforo (identificador A) (via via_1) (estado verde))
   (semaforo (identificador B) (via via_1) (estado verde))
   (semaforo (identificador C) (via via_1) (estado verde))
   (semaforo (identificador D) (via via_1) (estado verde))
   (semaforo (identificador A) (via via_2) (estado rojo))
   (semaforo (identificador B) (via via_2) (estado rojo))
   (semaforo (identificador C) (via via_2) (estado rojo))
   (semaforo (identificador D) (via via_2) (estado rojo))
   ;; Sensores
   (sensor (identificador 0) (semaforo A) (estado desactivado))
   (sensor (identificador 1) (semaforo A) (estado desactivado))
   (sensor (identificador 2) (semaforo A) (estado desactivado))
   (sensor (identificador 0) (semaforo B) (estado desactivado))
   (sensor (identificador 1) (semaforo B) (estado desactivado))
   (sensor (identificador 2) (semaforo B) (estado desactivado))
   (sensor (identificador 0) (semaforo C) (estado desactivado))
   (sensor (identificador 1) (semaforo C) (estado desactivado))
   (sensor (identificador 2) (semaforo C) (estado desactivado))
   (sensor (identificador 0) (semaforo D) (estado desactivado))
   (sensor (identificador 1) (semaforo D) (estado desactivado))
   (sensor (identificador 2) (semaforo D) (estado desactivado))
   ;; Sensores activados
   (sensor_activado 2 A 1234ASD)
   (sensor_activado 2 B 1234ABC)
   (sensor_activado 2 C 1234XYZ)
   (sensor_activado 2 D 1234IJK))

(defrule Registrar_info
   ?sensor_ <- (sensor (identificador 2) (semaforo ?semaforo) (estado desactivado) (vehiculo ?vehiculo))
   (semaforo (identificador ?semaforo) (via ?via) (estado ?estado))
   (vehiculo (matricula ?matricula) (tipo ?tipo) (via ?via))
   ?sensor_activado_ <- (sensor_activado ?sensor ?semaforo ?matricula)
   =>
   (modify ?sensor_ (estado activado) (vehiculo ?vehiculo))
   (printout t "el sensor " ?sensor " del semaforo " ?semaforo " ha sidentificadoro atravesado por el vehiculo de matricula " ?matricula " en la via " ?via crlf)
   (retract ?sensor_activado_))

(defrule Llegada_vehiculo
   ?vehiculo_ <- (vehiculo (matricula ?matricula) (tipo ?tipo) (via ?via) (accion ?accion))
   ?sensor_2_ <- (sensor (identificador 2) (semaforo ?semaforo) (estado activado) (vehiculo ?vehiculo))
   ?sensor_1_ <- (sensor (identificador 1) (semaforo ?semaforo_2) (estado desactivado) (vehiculo ?vehiculo_2))
   =>
   (modify ?vehiculo_ (accion llegando))
   (modify ?sensor_2_ (estado desactivado))
   (modify ?sensor_1_ (estado activado) (vehiculo ?vehiculo))
   (printout t "el " ?tipo " con matricula " ?matricula " esta llegando al cruce " crlf))

(deffunction contar_vehiculos (?valor)
   (+ ?valor 1))

(defrule Cruce_realizado
   ?sensor_ <- (sensor (identificador 0) (semaforo ?semaforo) (estado activado) (vehiculo ?vehiculo))
   ?vehiculo_ <- (vehiculo (matricula ?matricula) (tipo ?tipo) (via ?via) (accion ?accion))
   ?via_ <- (via (identificador ?identificador) (descripcion ?descripcion) (vehiculo ?vehiculo_2))
   =>
   (modify ?vehiculo_ (accion realizado))
   (modify ?via_ (vehiculo (contar_vehiculos ?vehiculo_2)))
   (printout t "el " ?tipo " con matricula " ?matricula " acaba de finalizar el cruce " crlf)
   (modify ?sensor_ (estado desactivado)))

(defrule Impedir_paso_vehiculo
   (vehiculo (matricula ?matricula) (tipo ?tipo) (via ?via) (accion ?accion))
   ?vehiculo_ <- (vehiculo (matricula ?matricula_2) (tipo ?tipo_2) (via ?via_2) (accion llegando))
   (sensor (identificador 1) (semaforo ?semaforo) (estado activado) (vehiculo ?vehiculo))
   (semaforo (identificador ?semaforo) (via ?via_2) (estado rojo))
   =>
   (modify ?vehiculo_ (accion esperando))
   (printout t "semaforo " ?semaforo " en rojo, el " ?tipo_2 " con matricula " ?matricula_2 " se encuentra esperando" crlf))
