#ifndef PACKAGEDATADEFINE_H
#define PACKAGEDATADEFINE_H

#pragma  pack(1)

//定义通信包数据结构
    //名称std::string统一用char[255]字节来接收发送
    //携带发射源的飞机目标（秦莹接收的真实目标发射源数据）
    typedef struct _FlyTargetInfo
    {
        char   sName[32];         //目标名称
        double dX;          //X值  （笛卡尔坐标系）
        double dY;          //Y值  （笛卡尔坐标系）
        double dZ;          //Z值  （笛卡尔坐标系）
        double dPsi;               //航向
        double dPhi;               //俯仰
        double dGamma;             //横滚
        double dSpeed;             //速度m/s
        int  nCamp;                //阵营1 = 红2 = 蓝3 = 白
        int  nState;			   // 状态 -1 = 初始化0 = 静止 1 = 飞行
        //目标携带雷达参数
        double dPower;	     //功率W
        double dFrequency;   //发射频率MHz
        double dBandWidth;   //带宽 MHz
        double dMainGain;    //主瓣增益dB
        double dNoise;       //噪声系数
        double dSNR;         //最小信噪比
        double dpulsetime;   //脉冲发出时间
    }FlyTargetInfo;
    //接收雷达用于定位的数据
    typedef struct _TargetInfo
    {
        char			sName[32];//目标名称
        unsigned int	sNum;   //目标编号
        double dX;          //X值，（笛卡尔坐标系）
        double dY;          //Y值  （笛卡尔坐标系）
        double dZ;          //Z值  （笛卡尔坐标系）
        double dpulsetime;  //脉冲发出时间
        double dtoa;     //脉冲到达时间（TOA）
        double dAoa;  //到达方向（AOA），相对方位角(向上为正，单位：弧度)
        double dElev;  //到达俯仰角angle of elevation，(向上为正，单位：弧度)
        int nRf;   //载频（RF）
        int nPW;   //脉宽（PW）
        int nPA;   //脉幅（PA）
    }TargetInfo;


//携带接收雷达的坦克（李东轩从HLA上接收使用的数据）
    typedef struct _TankActorInfo
    {
        char	sName[32];         //坦克名称
        double dX;                //X值 （笛卡尔坐标系）
        double dY;                //Y值 （笛卡尔坐标系）
        double dZ;                //Z值 （笛卡尔坐标系）
        double dPsi;               //航向
        double dPhi;               //俯仰
        double dGamma;             //横滚
        double dSpeed;             //速度m/s
        int  nCamp;                //阵营1 = 红2 = 蓝3 = 白
        int  nState;			   // 状态 -1 = 初始化0 = 静止 1 = 运动
        char	sSenserName[32];   //探测器名称
        bool bOpen;				    //探测器是否开机
        double dMaxDistance;	    //探测器最大探测距离（判断目标是否在探测距离之内）m

        int nTargetNum;				   //探测到的目标信息数量
        TargetInfo _targetInfoVec[10]; //探测到的目标信息参数容器
    }TankActorInfo;

    //定位计算结果返回数据结构（李东轩推送到HLA上的数据，秦莹接收的探测结果数据）
    typedef struct _ResultInfo
    {
        char    sSenserName[32] ;  //探测器名称
        char     sName[32];    //探测到目标名称
        unsigned int  sNum;     //探测到的辐射源编号。
        double dLocX;           //定位计算结果X值  （笛卡尔坐标系）
        double dLocY;           //定位计算结果Y值  （笛卡尔坐标系）
        double dLocZ;           //定位计算结果Z值  （笛卡尔坐标系）
        double dLocHead;        //定位计算结果航向角
        double dLocPitch;       //定位计算结果俯仰角
        double dLocRoll;        //定位计算结果翻滚角
        double dt;              //接收到的脉冲到达时间



    }ResultInfo;

#endif // PACKAGEDATADEFINE_H
