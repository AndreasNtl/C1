

Compile: make

Execute : ./main q k with max=2000000 OR ./main q k max (gia diaforetiko max )

Εχω φτιαξει ενα struck Fileline οπου θα κραταω καθε σελιδα απο τα 2 blocks , ενα struct Tableline

ειναι ενας πινακας οπου σε καθε γραμμη του σημειωνω αν ειναι κενη , αν ειναι clean ή αν ειναι

dirty , επισης σε καθε γραμμη αν δεν ειναι κενη εχω τον αριθμο της σελιδας και τ ονομα του block

που ανηκει η σελιδα. Επισης εχω ενα struct statistics για τα στατιστικα .

Σαρωνω τον πινακα Tableline και αναλογως το περιεχομενο καθε πλαισιου αποφασιζω για την

σελιδα την οποια εχω στη Fileline .

Μετα απο πολλες εκτελσεις με διαφορετικα 'k' παρατηρουμε οτι οταν αυξανουμε τα πλαισια

μειωνονται τα page faults.

Εκτελεσεις με διαφορετικα k:

-------------------------DATA----------------------------

number of q is 5

number of k is 100

number of frames is 200

number of max is 2000000

----------------------STATISTICS---------------------------

number of hits is 1929673

number of faults is 70327

number of reads is 70327

number of writes is 11762

-------------------------DATA----------------------------

number of q is 5

number of k is 50

number of frames is 100

number of max is 2000000

----------------------STATISTICS---------------------------

number of hits is 1898425

number of faults is 101575

number of reads is 101575

number of writes is 16569





-------------------------DATA----------------------------

number of q is 5

number of k is 200

number of frames is 400

number of max is 2000000

----------------------STATISTICS---------------------------

number of hits is 1951391

number of faults is 48609

number of reads is 48609

number of writes is 8371


