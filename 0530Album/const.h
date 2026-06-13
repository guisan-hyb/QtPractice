#ifndef CONST_H
#define CONST_H


enum TreeItemTyppe{
    TreeItemPro = 1, //表示项目的条目
    TreeItemDir = 2, //表示项目的文件夹
    TreeItemPic = 3  //表示项目的图片
};

const int PROGRESS_WIDTH = 300;
const int PROGRESS_MAX = 300;

enum PicBtnState {
    PicBtnStateNormal_o = 1,
    PicBtnStateHover_o = 2,
    PicBtnStatePress_o = 3,

    PicBtnStateNormal_c = 4,
    PicBtnStateHover_c = 5,
    PicBtnStatePress_c = 6,
};

const int PREITEM_SIZE = 100;
const int PREICON_SIZE = 90;

#endif // CONST_H

