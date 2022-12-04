# Tema_aplicatie
 An app that searches and books train tickets.
## LABORATOR 7
### Ștefănescu Denisa Raluca
### 322AC

#### Autentificarea
**Autentificarea** este, conform cuvântului din limba greacă autenticos, procesul prin care este dovedită veridicitatea unei afirmații, așa cum cineva pretinde.
Autentificarea se realizează în general cu ajutorul unor unui nume de utilizator și a unei parole. 
Un exemplu de autentificare din viața reală este prezentarea pașaportului la terminalul de check-in al unui aeroport pentru primirea talonul de îmbarcare.
#### Autorizarea
**Autorizarea** este procesul care urmează, în general, după autentificare, deoarece acesta acordă privilegii utilizatorului pentru diferite funcționalități 
ale unei aplicații, de obicei conform permisiunilor corespunzătoare nivelului de privilegiu (în cazul acestei aplicații, utilizatorii nu pot adauga sau șterge curse din baza de date). 
În cadrul acestui proiect, am implementat această diferențiere înca din meniul de login, după care am împărțit pe ramuri metodele pentru fiecare tip de cont.
Un exemplu din viața reală ar putea fi un dulap cu cheie. Persoana care deține dulapul (prin extensie, și cheia) poate garanta dreptul de acces la dulap oricui dorește.
#### Logarea
Login (sau logarea) este procesul prin care un utilizator primește acces în cadrul unui sistem. De multe  ori, login înseamnă chiar acreditările folosite la autentificare (nume de utilizator și parolă). Opusul logării este delogarea.
Logarea în general se realizează cu ajutorul următorilor pași:
1.	Utilizatorul intră în aplicație/program. Dacă sesiunea precedentă nu a fost incheiată, aceasta este de cele mai multe ori redirecționat către pagina de start a acelei aplicații.
2.	În caz contrar, utlizatorul este trimis către pagina de login, unde este rugat să își introducă acreditările (de cele mai multe ori numele de utilizator și parola, dar depinde de tipul de sistem/aplicație)
3.	Odată apăsat butonul de login, datele introduse de utilizator sunt preluate și comparate cu informațiile aflate într-o bază de date. Urmează apoi verificările – de exemplu, dacă parola introdusă de utilizator corespunde cu linia din baza de date. Alte verificări mai pot fi făcute, în funcție de specificul aplicației. 
4.	Se generează un token pentru sesiunea utilizatorului. Acesta îi oferă acces utilizatorului în sistem. De cele mai multe ori, acest token urmărește activitățile întreprinse în timpul sesiunii.
5.	Utilizatorul poate folosi aplicația până la expirarea token-ului sau până se deloghează singur.
Cea mai întâlnită metodă pentru a îmbunătăți securitatea login-ului într-o aplicație este 2FA (2 factor-authentication). De exemplu, pentru accesa un cont bancar, un utilizator este nevoit să introducă, pe lângă detaliile contului său, un PIN, care este cele mai multe ori emis de o aplicație de tip bank token (varianta modernă a bank token-ului cu butoane).
Cu toate acestea, nu este garantat un strat în plus de securitate dacă 2FA este implementat.  De pildă, dacă 2FA se realizează cu ajutorul SMS-ului, un simplu atac de tip phishing poate fi îndeajuns pentru ca atacatorii să fure datele utilizatorilor (cu atât mai simplu cu cât vorbim despre un atac de phishing în cadrul unei companii de telefonie mobilă).
Alte metode pentru sporirea securității sistemului la autentificare sunt utilizarea datelor biometrice sau utilizarea token-urilor, prin care se creează o legătură directă între sesiunea utilizatorului și aplicație.

Câteva mențiuni despre proiect:
•	Screenshoturile s-ar putea să nu arate fiecare aspect pe care l-am implementat. Există o posibilitate să fi uitat să fac poze (scuze)
•	Programul se rulează din terminal cu comenzile gpp *.cp -o run și .\run

