/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.0

Page {
    Container {
        layout: AbsoluteLayout {
            
        }
        ImageView {
            //imageSource: "asset:///images/highScore.png"
        }
        Container {
            //background: Color.Red
            preferredHeight: 50
            preferredWidth: 632
            layout: DockLayout {
                
            }
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 34.0
                positionY: 220.0
            }
            Label {
                textStyle.fontSize: FontSize.XLarge
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Bottom
                text: "3000"
            }
        }
        Container {
            //background: Color.White
            preferredHeight: 121
            preferredWidth: 632
            layout: DockLayout {
            
            }
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 34.0
                positionY: 299.0
            }
            Label {
                textStyle.fontSize: FontSize.XLarge
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Bottom
                text: "1000"
            }
        }
        Container {
            //background: Color.Blue
            preferredHeight: 108
            preferredWidth: 632
            layout: DockLayout {
            
            }
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 34.0
                positionY: 426.0
            }
            Label {
                textStyle.fontSize: FontSize.XLarge
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Bottom
                text: "2000"
            }
        }
        ImageView {
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 9.0
                positionY: 659.0
            }
            //imageSource: "asset:///images/shareHS.png"
        }
        /*ImageView {
            imageSource: "asset:///images/tree/resume.png"
        }
        ImageView {
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 238.0
                positionY: 260.0
            }
            imageSource: "asset:///images/tree/resumeButton.png"
        }*/
        /*ImageView {
            imageSource: "asset:///images/tree/treeBG.png"
        }
        ImageView {
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 15.0
                positionY: 147.0
            }
            imageSource: "asset:///images/tree/1.png"
        }
        ImageView {
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 52.0
                positionY: 406.0
            }
            imageSource: "asset:///images/tree/2.png"
        }
        ImageView {
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 362.0
                positionY: 428.0
            }
            imageSource: "asset:///images/tree/3.png"
        }
        ImageView {
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 370.0
                positionY: 541.0
            }
            imageSource: "asset:///images/tree/4.png"
        }*/
    }
}
