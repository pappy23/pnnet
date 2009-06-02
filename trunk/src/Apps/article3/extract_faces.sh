#!/bin/bash

#Usage:
#put this script in ~/faces_db
#~/faces_db/orl_faces/s* durectories must exist
#run and enjoy!
#see ~/faces_db/combined/ for results
#...
#PROFIT!

#Dependencies
#imagemagick
#netpbm
#rand utility

FACE_W=92
FACE_H=92
PIC_W=140
PIC_H=140
BORDER=10

echo "Extracting faces from original orl_faces"
mkdir -p orl_extracted
cd orl_faces
for i in `\ls -1`; do
    cd $i
    for j in `\ls -1 *pgm`; do
        convert $j \
            -gravity South \
            -crop 92x92+0+0 \
            -scale ${FACE_H}x${FACE_W} \
            ../../orl_extracted/${i}_${j}
    done
    cd ..
done
cd ..

echo "Generating backgrounds"
mkdir -p backgrounds
cd backgrounds
for i in `seq 1 10`; do
    ppmmake `rand -f -d ',' -N 3` $PIC_H $PIC_W | ppmtopgm > $i.pgm
done
cd ..

echo "Combining faces with backgrounds"
mkdir -p combined
cd orl_extracted
RANDOMS_H=( `rand -N 4000 -M $(($PIC_H - 2 * $BORDER - $FACE_H))` )
RANDOMS_W=( `rand -N 4000 -M $(($PIC_W - 2 * $BORDER - $FACE_W))` )

COUNTER=0
for i in `\ls -1 *.pgm`; do
    COUNTER=$(( $COUNTER + 1 ));
    for j in `seq 1 4`; do
        BG=`\ls -1 ../backgrounds/* | sort -R | head -1`
        convert $BG $i -geometry "+$(( ${RANDOMS_H[$(( $COUNTER * 4 + j ))]} \
        + $BORDER ))+$(( ${RANDOMS_W[$(( $COUNTER * 4 + j))]} + $BORDER ))" \
        -composite ../combined/${i}_${j}.pgm
    done
done
cd ..

echo "Introducing noise"
cd combined
for i in `\ls -1 *pgm`; do
    convert $i -normalize +noise Impulse ${i}_impulse1.pgm
    convert ${i}_impulse1.pgm +noise Impulse ${i}_impulse2.pgm
    mv $i ${i}_original.pgm
done
rename 's/\.pgm_/_/' *
rename 's/\.pgm_/_/' *
cd ..

