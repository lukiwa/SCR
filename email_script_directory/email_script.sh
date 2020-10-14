#!/bin/bash


sender_mail="lukasz@scr.com"
body=tresc.txt
addresses=adresy.txt
subject="Zapytanie ofertowe"
attachments="spec*.pdf"



full_from_formula="my_hdr From:";
full_from_formula+=$sender_mail;


while IFS= read -r address; do
    mutt -s $subject $address -a $attachments -e "$full_from_formula" < $body
done < $addresses

