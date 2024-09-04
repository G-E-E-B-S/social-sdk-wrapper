// FIXME: this import won't work on cocos 2.x, need to make this work somehow
import { Component } from "cc";

export type IShareInitCallback = (success : boolean) => void; 

export default interface IShareContent extends Component {
    init(initParams : unknown, completeCallback : IShareInitCallback);
}

