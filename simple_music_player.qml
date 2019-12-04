import QtQuick 2.2
import QtMultimedia 5.0
Rectangle {
    width: 320;
    height: 240;
    color: "black";
    
    property var utilDate: new Date();
    
    function msecs2String(msecs){
        utilDate.setTime(msecs);
        return Qt.formatTime(utilDate, "mm:ss");
    }

    MediaPlayer {
        id: player;
        source: "wangjie_game_and_dream.mp3";
        onPositionChanged: {
            progress.text = msecs2String(position) + progress.sDuration;
        }
        onDurationChanged: {
            progress.sDuration = " / " + msecs2String(duration);
        }
        onPlaybackStateChanged: {
            switch(playbackState){
            case MediaPlayer.PlayingState:
                state.text = "播放中";
                break;
            case MediaPlayer.PausedState:
                state.text = "已暂停";
                break;
            case MediaPlayer.StoppedState:
                state.text = "停止";
                break;                                
            }
        }
        onStatusChanged: {
            switch(status){
            case MediaPlayer.Loaded:
                console.log(metaData.albumArtist, metaData.albumTitle, metaData.author, metaData.channelCount);
                break;
            }
        }
    }
    
    Row {
        id: controller;
        anchors.top: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.topMargin: 4;
        spacing: 4;
        FlatButton {
            width: 50;
            height: 50;
            iconSource: "ic_rew.png";
            onClicked: if(player.seekable)player.seek(player.position - 5000);
        }
        FlatButton {
            width: 50;
            height: 50;        
            iconSource: "ic_pause.png";
            onClicked: player.pause();
        }
        FlatButton {
            width: 50;
            height: 50;        
            iconSource: "ic_play.png";
            onClicked: player.play();
        } 
        FlatButton {
            width: 50;
            height: 50;        
            iconSource: "ic_stop.png";
            onClicked: player.stop();
        }               
        FlatButton {
            width: 50;
            height: 50;        
            iconSource: "ic_ff.png";
            onClicked: if(player.seekable)player.seek(player.position + 5000);
        }        
    }
    Text {
        id: progress;
        anchors.left: controller.left;
        anchors.bottom: controller.top;
        anchors.bottomMargin: 4;
        color: "white";
        font.pointSize: 12;
        property string sDuration;
    }
    Text {
        id: state;
        anchors.left: progress.left;
        anchors.bottom: progress.top;
        anchors.bottomMargin: 4;
        color: "white";
        font.pointSize: 12;
    }
    Text {
        id: metaInfo;
        anchors.left: state.left;
        anchors.bottom: state.top;
        anchors.bottomMargin: 4;
        color: "blue";
        font.pointSize: 14;    
    }
}
