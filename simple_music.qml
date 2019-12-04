import QtQuick 2.2
import QtMultimedia 5.0
Rectangle {
    width: 200;
    height: 100;

    MediaPlayer {
        autoPlay: true;
        source: "wangjie_game_and_dream.mp3";
    }
}
