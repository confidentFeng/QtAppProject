import QtQuick 2.2
import QtMultimedia 5.0
Rectangle {
    width: 720;
    height: 480;

    MediaPlayer {
        id: player;
        source: "D:/FavoriteVideo/Tom_Jerry_001.flv";
        /*
        onError: {
            console.log(errorString);
        }
        onStatusChanged: {
            switch(status){
            case MediaPlayer.Loaded:
                var mediaObj = mediaObject;
                console.log(player);
                for(var prop in mediaObj){
                    console.log("prop -", prop, " value-", player[prop]);
                }
                //console.log(metaData.resolution, metaData.videoCodec, metaData.videoBitrate, metaData.videoFrameRate);
                
                break;
            }
        }      
        
        function readMeta(){
            console.log(metaData.resolution, metaData.videoCodec, metaData.videoBitrate, metaData.videoFrameRate);
        }
        onMediaObjectChanged:{
            console.log("mediaobject changed");
            var mediaObj = mediaObject;
            mediaObj.metaDataChanged.connect(readMeta);            
        }  
        */
    }
    
    VideoOutput {
        anchors.fill: parent;
        source: player;
    }
    
    MouseArea {
        anchors.fill: parent;
        onClicked: {
            console.log("call play");
            player.play();
        }
    }
}
