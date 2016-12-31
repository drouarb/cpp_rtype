#!/usr/bin/env bash

echo "{"
echo "  name: \"basic\","

echo "  spawns:
  [
"

function addWall() {
    echo -n "    {
      dlName: \"build/entity/libObstacle\",
      time: \"10\",
      posX: \"$1\",
      posY: \"$2\"
    }"
}

I=0
while [ $I -ne 1800 ]
do
    addWall $I 0
    I=$(($I+100))
    echo ","
done

I=0
while [ $I -ne 1800 ]
do
    addWall $I 1050
    echo ","
    I=$(($I+100))
done

I=0

function addEntity() {
    echo "    {
      dlName: \"$1\",
      time: \"$2\",
      posX: \"$3\",
      posY: \"$4\"
    },
"
}

while [ $I -le 2000 ]
do
    NB=$(($RANDOM % 5 + 1))

    LAST=0

    while [ $NB -ne 0 ]
    do
        case $(($RANDOM % 4 + 1)) in
        "1")
        addEntity "build/entity/libCrazyEntity" $I 1920 $(($RANDOM % 800 + 50))
        ;;
        "2")
        addEntity "build/entity/libBasicNastyEntity" $I 1920 $(($RANDOM % 800 + 50))
        ;;
        "3")
        addEntity "build/entity/libBomber" $I 1920 $(($RANDOM % 800 + 50))
        ;;
        "4")
        addEntity "build/entity/libOstwind" $I 1920 920
        ;;
        esac
        echo -n ""
        NB=$(($NB - 1))
    done

    I=$((I+$(($RANDOM % 50 + 150))))
done

addWall 0 0

echo "
    ],
  gamedata:
  [
      {
	  time: \"1\",
	  background: \"backgrounds/normal.png\",
	  music: \"musics/wind.ogg\"
      },
      {
	  time: \"200\",
	  background: \"backgrounds/nightfall.png\",
	  music: \"musics/Lady_Crimson.ogg\"
      }
  ]
  }
"