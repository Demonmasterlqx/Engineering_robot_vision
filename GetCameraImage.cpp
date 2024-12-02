#include "GetCameraImage.hpp"

static void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser){
    if (pFrameInfo){
        printf("GetOneFrame, Width[%d], Height[%d], nFrameNum[%d]\n", 
            pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameNum);
        
        cv::Mat mat(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1, pData);
        cv::Mat imageRGB;
        cv::cvtColor(mat, imageRGB, cv::COLOR_BayerRG2RGB);
        cv::imshow("1",imageRGB);
        cv::waitKey(2);
    }
}


bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo){
    if (NULL == pstMVDevInfo){
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE){
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);
        // ch:打印当前相机ip和用户自定义名字 | en:print current ip and user defined name
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chModelName);
        printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE){
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chModelName);
        printf("UserDefinedName: %s\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
    }
    else{
        printf("Not support.\n");
    }
    return true;
}

void Grabbing(){
    char c=getchar();
    while (c!='\n'&&c!=EOF) c=getchar();
    fprintf( stderr, "\nPress enter to exit.\n");
    while(getchar()!='\n');
}

void VideoGet(){
    int Sign=0;
    Sign=MV_CC_Initialize();
    if(Sign!=MV_OK){
        cout<<"Initialisze fail with error code "<<Sign<<endl;
        return;
    }
    MV_CC_DEVICE_INFO_LIST Devlist;
    memset(&Devlist,0,sizeof Devlist);
    Sign=MV_CC_EnumDevices(MV_USB_DEVICE,&Devlist);
    if(Sign!=MV_OK){
        cout<<"MV_CC_EnumDevices fail with error code "<<Sign<<endl;
        return;
    }
    if(!Devlist.nDeviceNum){
        cout<<"No Camera be found!\n";
        return;
    }
    //相机已近找到啦

    MV_CC_DEVICE_INFO ChoosedCamera;
    bool choosed=0;

    while(!choosed){
        for(int i=0;i<Devlist.nDeviceNum;i++){
            cout<<"No. "<<i<<endl;
            PrintDeviceInfo(Devlist.pDeviceInfo[i]);
        }
        int index=0;
        // std::cin>>index;
        //选择相机
        if(index>=Devlist.nDeviceNum){
            printf("Intput error!\n");
        }
        else ChoosedCamera=*Devlist.pDeviceInfo[index],choosed=1;
    }
    //相机选好啦

    void* handle;
    Sign=MV_CC_CreateHandle(&handle,&ChoosedCamera);
    if(Sign!=MV_OK){
        cout<<"MV_CC_OpenDevice fail with error code "<<Sign<<endl;
    }
    //创建句柄

    Sign=MV_CC_SetEnumValue(handle, "TriggerMode", 0);
    //这个地方挖个坑，有些东西可以看QWQ
    if(Sign!=MV_OK){
        cout<<"MV_CC_SetTriggerMode fail with code "<<Sign<<endl;
        return;
    }
    //设置相机模式

    Sign=MV_CC_RegisterImageCallBackEx(handle,ImageCallBackEx,0);
    if(Sign!=MV_OK){
        cout<<"MV_CC_RegisterImageCallBackEx fail with code "<<Sign<<endl;
        return;
    }
    //注册API

    Sign=MV_CC_StartGrabbing(handle);
    if(Sign!=MV_OK){
        cout<<"MV_CC_StartGrabbing fail with code "<<Sign<<endl;
        return;
    }

    Grabbing();

    Sign=MV_CC_StopGrabbing(handle);
    if(Sign!=MV_OK){
        cout<<"MV_CC_StopGrabbing fail with code "<<Sign<<endl;
        return;
    }
    //停止取流

    Sign=MV_CC_CloseDevice(handle);
    if(Sign!=MV_OK){
        cout<<"MV_CC_CloseDevice fail with code "<<Sign<<endl;
        return;
    }
    //关闭相机

    Sign=MV_CC_DestroyHandle(handle);
    if(Sign!=MV_OK){
        cout<<"MV_CC_DestroyHandle fail with code "<<Sign<<endl;
        return;
    }
    //销毁句柄
    handle = NULL;
    MV_CC_Finalize();
    //反初始化SDK

}