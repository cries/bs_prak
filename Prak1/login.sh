#!/usr/bin/sh


hour=`date +%H`


if [ $hour -ge "6" ] && [ $hour -lt "9" ]; then
	msg="Morgen"
elif [ $hour -ge "9" ] && [ $hour -lt "15" ]; then
	msg="Tag" 
elif [ $hour -ge "15" ] && [ $hour -lt "18" ]; then
	msg="Nachmittag"
elif [ $hour -ge "18" ] && [ $hour -lt "23" ]; then
	msg="Abend"
fi

echo "Guten $msg $USER, es ist `date +%H:%M` Uhr."
sz=`du -ks ~ | cut -f1`
sz=`expr $sz / 1024`
echo "Das Homeverzeichnis belegt $sz MB."
