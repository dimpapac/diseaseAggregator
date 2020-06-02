Δημήτρης Παπαχρήστου 
ΑΜ: 1115201500124
Κ24: Προγραμματισμός Συστήματος 

Τα αρχεία κώδικα είναι: 
1. diseaseAggregator.c
2. Worker.c
3. rbt.c
4. list.c
5. heap.c
6. functions.c 
7. functions1.c 

Τα αρχεία επικεφαλίδας είναι:
1. structs.h 
2. rbt.h
3. list.h
4. heap.h
5. functions.h
6. functions1.h 

Για το script: 
countriesFile
diseaseFile
create_infiles.sh

Makefile: 
Με την εντολή make γίνεται η μεταγλώττιση των αρχείων και με την εντολή make run εκτελείται 
το πρόγραμμα με βάση τα ορίσματα που δίνονται στο makefile (γραμμή 18)
Για διευκόλυνση υπάρχει και η εντολή make val (αντί για make run) και το πρόγραμμα εκτελείται 
με valgrind (valgrind -v --leak-check=full --show-leak-kinds=all)  

Χρησιμοποιήθηκαν οι δομές της πρώτης εργασίας άρα και τα αρχεία τους με μερικές αλλαγές για 
την απάντηση των ερωτημάτων αυτής της εργασίας. Ουσιαστικά οι νέες συναρτήσεις που υλοποίησα για 
diseaseAggregator και Workers βρίσκονται στο functions.c 


Σχεδιαστικές επιλογές:

Αν και τα named-pipes μπορούν να είναι bi-directional,
χρησιμοποιούνται 2 uni-directional ανάμεσα σε 2 διεργασίες
ένα για γράψιμο και ένα για διάβασμα αντίστοιχα από κάθε 
διεργασία.

Γίνεται χρήση της execvp για την δημιουργία των Workers.

Το πρωτόκολλο επικοινωνίας ανάμεσα στις δύο διεργασίες είναι το εξής: 
Αρχικά γράφω στο fifo έναν ακέραιο(int) που ενημερώνει το άλλο process για το μέγεθος του buffer
που θα γράψω στην συνέχεια και μετά γράφω τον buffer με το μήνυμα.
O diseaseAggregator κάνει open το fifo με O_NONBLOCK flag ενώ οι Workers όχι. 

 
Δεν έχουν υλοποιηθεί: 
Topk-AgeRanges
προσθήκη αρχείων 
αιφνίδιος θάνατος worker

