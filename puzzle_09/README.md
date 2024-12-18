https://aceptaelreto.com/problem/statement.php?id=461

Para su próxima ofensiva, el ejército rebelde ha decidido conquistar varias de las bases enemigas cercanas al planeta Polis Massa. Para eso ha estimado el mínimo número de soldados que necesitará para tener unas mínimas garantías de conquistar cada base enemiga, así como el número de bajas esperadas. Además, se espera que las fuerzas imperiales no se queden con los brazos cruzados ante cada conquista, por lo que es necesario dejar un retén militar permanente en las bases conquistadas, para impedir que sean recuperadas por el enemigo.

El número de efectivos para la ofensiva es limitado, por lo que se ha decidido atacar las bases imperiales de una en una. El orden no está fijado, y se quiere elegir aquél que minimice el número total de soldados necesarios para conquistarlas todas. Tu misión, si decides aceptarla, es determinar ese número.

Cada caso de prueba comienza con el número 1 ≤ N ≤ 1.000 de bases enemigas. A continuación vendrán N líneas, una por cada base. Para cada una se indican tres valores, la cantidad mínima de soldados necesarios para conquistar la base, s, las bajas esperadas, b, y el número de soldados que habrá que dejar como retén tras la batalla, r. Se garantiza que 0 ≤ b ≤ s ≤ 1.000 y 0 ≤ r ≤ 1.000.

Un caso sin bases, que no deberá procesarse, marca el final.

# Ejemplo
2
100 0 10
90 30 20
Solución: 100
3
50 40 20
20 20 30
50 10 5
Solución: 125

NOTA: Para conseguir conquistar las tres bases del segundo ejemplo con 125 soldados hay que empezar conquistando la última (50 10 5). El orden en el que se ataquen después las otras dos es indiferente.
