import bb.cascades 1.0

Container {
    layout: AbsoluteLayout {
    
    }
    ImageView {
        imageSource: "asset:///images/resultBoard/1280.png"
    }
    Container {
        layout: AbsoluteLayout {
        
        }
        layoutProperties: AbsoluteLayoutProperties {
            positionX: 254
            positionY: 0
        }
        ImageView {
            imageSource: "asset:///images/resultBoard/BG.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 155
                positionY: 55
            }
        }
        Container {
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 162
                positionY: 150
            }
            ImageView {
                imageSource: "asset:///images/resultBoard/1.png"
                
            }
        }
        ImageView {
            imageSource: "asset:///images/resultBoard/2.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 162
                positionY: 382
            }
        }
        ImageView {
            imageSource: "asset:///images/resultBoard/3.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 162
                positionY: 492
            }
        }
        ImageView {
            imageSource: "asset:///images/resultBoard/4.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 160
                positionY: 609
            }
        }
    }
}
