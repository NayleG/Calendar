Увод в програмирането (практикум)

2022-2023 г.

Задание за курсов проект № 10 - Календар

Програмата е свързана с работа с календар и управление на различни събития, като тя има няколко функционалнности.

Начално меню
Когато стартираме програмата на екрана се изписват днешната дата, ден, месец и година. Освен това се извежда и списък със събията от днес, а ако няма събития се извежда броя на събитията на следващия ден. При стартирането се извежда и меню със самите функционалности на програмата, от които потребителят избира какво иска да прави. 
Менюто изглежда по следния начин

Choose an option:
1. Show calendar
2. Show schedule
3. List events
4. Add event
5. Remove event
6. Set first weekday


Първа опция: 

Извежда календар на избрани от нас месец и година (проверява първо дали са въведени валидни месец и година), като ако през този месец има някакви събития, се извежда броя на събитията (!=0) през всеки ден, до определената дата в (). Освен това ако днешния ден е от този месец, той и деня, в който е, са отбелязани с []

Втора опция: 

Извежда всички събития до момента, сортирани по началната им дата, а ако има събития с еднакви начални дати, те се сортират по име в азбучен ред. За всяко събитие е изписан периодът, в който то протича (ако периода е само един ден, се изписва само неговата начална дата)

Tрета опция:

Извежда график за избрани от нас месец и година (проверява първо дали са въведени валидни месец и година), който показва събитията във всеки ден, в който има събития. Всяко принтирано събитие е озаглавено с датата и деня от седмицата. А ако в даден ден има повече от едно събитие, събитията в него са подредени по азбучен ред и само първото е озаглавено с дата и ден. Освен това ако дадено събитие е по-дълго от един ден, то се повтаря за всеки ден, в който протича, като се обозначава и поредният ден от събитието.

Четвърта опция: 

Служи за добавяне на събитие. За всяко събитие пишем име, начална дата и крайна дата. Ако вече съществува събитие с такова име ще изведе грешка (There is already such event!) и няма да се създаде такова събитие, защото вече съществува. Също ако една от датите (начална/крайна) е грешна или началната дата е след крайната се извежда отново грешка (Incorrect date!) и събитието няма да се запази.

Пета опция: 

С нея трием събития, като въведем името а събитието, което искаме да изтрием. Ако няма такова събитие - извежда се съобщението: There is no such event!.

Шеста опция:
Сменяме първия ден от седмицата в календара. Имаме опциите той да бъде Понеделник или Неделя (Mon/Sun). При въвеьданена нещо различно от Mon или Sun се извежда съобщение за грешка: Invalid day!

При избиране на цифра различна от 1,2,3,4,5,6 се извежда съобщение, че няма такъв избор;

