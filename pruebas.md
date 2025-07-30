🧪 1. Pruebas básicas (sin límite de comidas)
🔹 Caso 1.1 — Filósofos deben comer indefinidamente ./philo 2 800 200 200

Esperado:
- Dos filósofos comen, duermen y piensan sin morir.
- Salida cíclica continua (hasta que lo detengas con Ctrl+C).
- Ningún "died".

🔹 Caso 1.2 — Uno debe morir por inanición ./philo 2 310 200 200

Esperado:
- Uno de ellos morirá porque el segundo no puede comer a tiempo.
- Deberías ver una línea como:
[XXX] -> Philo[1] died. RIP.

🧪 2. Pruebas con meals_required (debe terminar automáticamente)
🔹 Caso 2.1 — Todos deben comer exactamente 7 veces ./philo 5 800 200 200 7

Esperado:
- Todos comen al menos 7 veces.
- La simulación finaliza automáticamente.
- Última línea debe ser: All philosophers ate enough

🔹 Caso 2.2 — Todos comen más de 7 veces (ok) ./philo 5 1000 50 50 7

Esperado:
- Salida rápida.
- Algunos comen 8, 9 o más veces.
- Simulación termina correctamente con "All philosophers ate enough".

🔹 Caso 2- 3 — Alguno muere antes de alcanzar meals_required ./philo 5 300 200  200 7

Esperado:
- Al menos un filósofo muere antes de completar 7 comidas.
- Mensaje de "died. RIP", pero NO "All philosophers ate enough".

🧪 3. Pruebas de carrera / sincronización
🔹 Caso 3.1 — 1 filósofo (caso límite) ./philo 1 800 200 200

Esperado:
- Filósofo agarra solo un tenedor, nunca puede comer.
- Muere tras 800 ms.

Mensaje: "Philo[1] died. RIP."

🔹 Caso 3.2 — Máxima contención ./philo 199 800 200 200

Esperado:
- No debe crashear ni colgarse.

Simulación debe correr (aunque lentamente).
- Se verifica que no haya errores de malloc, overflow o segmentation fa- lts.

🧪 4. Casos con valores extremos
🔹 Caso 4.1 — Tiempos muy cortos (riesgo de desincronización) ./philo 4 60 20 20
- sperado:
- - osible muerte rápida por no comer a tiempo.
- Muestra si el sistema gestiona correctamente sleeps precisos.

🔹 Caso 4.2 — Tiempos muy largos (más difícil que mueran) ./philo 4 10000 300 300

Esperado:
- Na- ie muere.
- Debe- ías ver comportamiento estable a largo plazo.

🧪 5. Errores silenciosos
🔹 Caso 5.1 — Verifica que no se imprimen cosas después de una muerte ./philo 3 310 200 200

Esperado- 
- Se impri- e solo un "died. RIP".
- Después de- eso, ninguna línea más debe aparecer.

🔹 Caso 5.2 — Salida limpia después de "All philosophers ate enough" ./philo 3 1000 100 100 5

Esperado:
- Imprime muchas acciones.
- Termina con - All philosophers ate enough".
- No imprime más- acciones tras ese mensaje.

🧪 6. Repeticiones para detectar condiciones de carrera
Repite cualquier prueba varias veces en bucle:
 for i in {1..100}; do ./philo 5 310 200 100; done

Esperado:
- Nunca debe colgarse ni crashear.
- Siempre debe imprimir una única muerte y luego terminar.

7. ./philo 5 800 200 200
- No philosopher should die.

8. ./philo 5 800 200 200 7
- No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times

9. ./philo 4 410 200 200
- No philosopher should die

10. ./philo 4 310 200 100
- One philosopher should die