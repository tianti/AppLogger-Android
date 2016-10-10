#ifndef _APPLOGGER_H_
#define _APPLOGGER_H_
#include <string>
using std::string;

//
// AppLogger,AppConfig 为sdk接口的C++封装
// 放到所接入程序的源代码目录
//

#define STAGE_NULL		"@null"    // 空，没有关卡/页面
#define STAGE_MAX		"@max"     // 最大关卡
#define STAGE_LAST		"@last"    // 最后关卡，缺省
#define STAGE_CURRENT	"@current" // 当前关卡或页面

#ifndef NULL
    #define NULL 0
#endif

#define DEBUG_MODE_OFF       0 // 不输出调试信息
#define DEBUG_MODE_LOGCAT    1 // 用于联机调试 android下输出到logcat ios下输出到console
#define DEBUG_MODE_LOGFILE   2 // 输出到 文件（applogger.log）, 用于脱机调试
#define DEBUG_MODE_LOGALL    3 // 输出到 logcat/console 和 文件（applogger.log）

#define DEBUG_LEVEL_VERBOSE  0 // 输出所有级别调试信息
#define DEBUG_LEVEL_INFO     1 // 输出INFO级别以上调试信息
#define DEBUG_LEVEL_WARN     2 // 输出WARN级别以上调试信息
#define DEBUG_LEVEL_ERROR    3 // 输出ERROR级别以上调试信息

#if defined(__ANDROID__) && !defined(TT_PREBUILT)
#include <dlfcn.h>
static void* dlFun(const char* funName) {
    void* fn = NULL;
    void* handle = dlopen("liblogger.so", RTLD_LAZY);
    if (handle) {
        fn = dlsym(handle, funName);
        dlclose(handle);
    }
    return fn;
}

#define TT_FUN(t, ...) \
        typedef t (*fn_t)(__VA_ARGS__); \
        fn_t fn = reinterpret_cast<fn_t>(dlFun(__FUNCTION__));

#define TT_EXECUTE_(...) \
        if (fn) fn(__VA_ARGS__);

#define TT_EXECUTE_RET_(r,...) \
        if (fn) return fn(__VA_ARGS__);  \
        else return r;

#define TT_EXECUTE(t,...) TT_EXIT_ ## t(__VA_ARGS__)
#define TT_EXIT_void(...) \
        TT_EXECUTE_(__VA_ARGS__);
#define TT_EXIT_int(...) \
        TT_EXECUTE_RET_(-1, __VA_ARGS__)

static void logger_init (const char* appKey, const char* appChannel) {
    TT_FUN(void, const char*, const char*);
    TT_EXECUTE(void, appKey, appChannel);
}
static void logger_setDebugLog(int mode, int level) {
    TT_FUN(void, int, int);
    TT_EXECUTE(void,mode, level);
}
static void logger_setSessionInterval (int v) {
    TT_FUN(void, int);
    TT_EXECUTE(void, v);
}
static void logger_setOnline (bool bOnline) {
    TT_FUN(void, bool);
    TT_EXECUTE(void, bOnline);
}
static void logger_enableCrashReport() {
    TT_FUN(void, void);
    TT_EXECUTE(void);
}
static void logger_enableOnlineConfig() {
    TT_FUN(void, void);
    TT_EXECUTE(void);
}
static int  logger_getParamValue(const char *param, char *value, int len, const char *defValue) {
    TT_FUN(int, const char *, char *, int , const char *);
    TT_EXECUTE(int,param, value, len,defValue);
}
static void logger_onStart () {
    TT_FUN(void, void);
    TT_EXECUTE(void );
}
static void logger_onEnd () {
    TT_FUN(void, void);
    TT_EXECUTE(void);
}
static void logger_onExit () {
    TT_FUN(void, void);
    TT_EXECUTE(void);
}
static int  logger_onSubStart (const char* name) {
    TT_FUN(int, const char*);
    TT_EXECUTE(int, name);
}
static void logger_onSubEnd (const char* stage) {
    TT_FUN(void, const char*);
    TT_EXECUTE(void, stage);
}
static void logger_onPassFail (bool bPass) {
    TT_FUN(void, bool);
    TT_EXECUTE(void, bPass);
}
static void logger_onEvent (const char* name, const char* stage) {
    TT_FUN(void, const char*, const char*);
    TT_EXECUTE(void, name, stage);
}
static void logger_onBalance (const char* name, const char* item, int value, const char* stage) {
    TT_FUN(void, const char*, const char*, int, const char*);
    TT_EXECUTE(void, name, item, value, stage);
}
static void logger_onLevelUp (const char* name, const char* oldLevel, const char* newLevel, const char* stage) {
    TT_FUN(void, const char*, const char*, const char*, const char*);
    TT_EXECUTE(void, name, oldLevel, newLevel, stage);
}
static void logger_onBuy (const char* service, const char* item, int count, float value, const char* stage) {
    TT_FUN(void, const char*, const char*, int, float, const char* );
    TT_EXECUTE(void, service, item, count, value, stage);
}
static void logger_onUse (const char* item, int count, const char* stage) {
    TT_FUN(void, const char*, int, const char*);
    TT_EXECUTE(void, item, count, stage);
}
static void logger_onExchange (const char* item, int count, const char* stage) {
    TT_FUN(void, const char*, int, const char*);
    TT_EXECUTE(void, item, count, stage);
}
static void logger_onCollect (const char* item, int count, const char* stage) {
    TT_FUN(void, const char*, int, const char*);
    TT_EXECUTE(void, item, count, stage);
}
static void logger_onReward (const char* item, int count, const char* stage) {
    TT_FUN(void, const char*, int, const char*);
    TT_EXECUTE(void, item, count, stage);
}
static void logger_onShare (const char* service, const char* item, const char* stage) {
    TT_FUN(void, const char*, const char*, const char*);
    TT_EXECUTE(void, service, item, stage);
}
static void logger_onError (const char* type, const char* msg) {
    TT_FUN(void, const char*, const char*);
    TT_EXECUTE(void, type, msg);
}
static void logger_clearStatus() {
    TT_FUN(void, void);
    TT_EXECUTE(void);
}
static void logger_setStatus(const char* key, int value, bool bAutoConvert) {
    TT_FUN(void, void);
    TT_EXECUTE(void);
}
static void logger_setUser (const char* level, int age, const char* gender, const char* userId, const char* userService) {
    TT_FUN(void, const char*, int, const char*, const char*, const char*);
    TT_EXECUTE(void, level, age, gender, userId, userService);
}

#else

#ifdef __cplusplus
extern "C" {
#endif
    void logger_init (const char* appKey, const char* appChannel);
    void logger_setDebugLog(int mode, int level);
    void logger_setSessionInterval (int v);
    void logger_setOnline (bool bOnline);
    void logger_enableCrashReport();
    void logger_enableOnlineConfig();
    int  logger_getParamValue(const char *param, char *value, int len, const char *defValue);
    void logger_onStart ();
    void logger_onEnd ();
    void logger_onExit ();
    int  logger_onSubStart (const char* name);
    void logger_onSubEnd (const char* stage);
    void logger_onPassFail (bool bPass);
    void logger_onEvent (const char* name, const char* stage);
    void logger_onBalance (const char* name, const char* item, int value, const char* stage);
    void logger_onLevelUp (const char* name, const char* oldLevel, const char* newLevel, const char* stage);
    void logger_onBuy (const char* service, const char* item, int count, float value, const char* stage);
    void logger_onUse (const char* item, int count, const char* stage);
    void logger_onExchange (const char* item, int count, const char* stage);
    void logger_onCollect (const char* item, int count, const char* stage);
    void logger_onReward (const char* item, int count, const char* stage);
    void logger_onShare (const char* service, const char* item, const char* stage);
    void logger_onError (const char* type, const char* msg);
    void logger_clearStatus();
    void logger_setStatus(const char* key, int value, bool bAutoConvert);
    void logger_setUser (const char* level, int age, const char* gender, const char* userId, const char* userService);
#ifdef __cplusplus
}
#endif

#endif //TT_PREBUILT

class AppLogger
{
public:
    /*********************************************************************************
     * 设置接口，调用顺序上可以任意，不依赖与AppLogger::init
     *
     *********************************************************************************/
    
    //调试日志输出方式，默认关闭
    static void setDebugLog(int mode, int level) {logger_setDebugLog(mode, level);}
    
    //设置session间隔 单位秒，android下默认30秒，iOS下默认0秒
    static void setSessionInterval (int v) {logger_setSessionInterval(v);}
    
    //是否发送统计数据，不调用此接口时默认发送状态。
    //可用作过滤非登录启动：
    //AppLogger::init调用前后，可调用AppLogger::setOnline(false),此时数据不发送；
    //等登录成功后，调用AppLogger::setOnline(true),即可发送统计数据
    static void setOnline (bool bOnline) {logger_setOnline(bOnline);}
    
    //开启崩溃报告
    static void enableCrashReport() {logger_enableCrashReport();}
    
    //开启在线参数功能，不调用此接口，无法更新统计后台配置的在线参数列表
    static void enableOnlineConfig() {logger_enableOnlineConfig();}
    
    /*********************************************************************************
     * 接口名称: getOnlineConfig
     * 功   能: 获取指定的在线参数(必须在AppLogger::init()后使用)
     *
     *********************************************************************************/
    
    //根据在线参数后台配置的参数名称，来获取对应的参数值
    static string getOnlineConfig(string param, string defValue="")
    {
        int nLen = logger_getParamValue(param.c_str(), NULL, 0, NULL);
        string strValue;
        if (nLen > 0) {
            char *str = new char[nLen+1];
            memset(str, 0, (nLen+1)*sizeof(char));
            logger_getParamValue(param.c_str(), str, nLen+1, defValue.c_str());
            strValue = str;
            delete [] str;
        }
        else if (nLen == -1) {//查询不到此参数，使用默认值
            strValue = defValue;
        }
        
        return strValue;
    }

    /*********************************************************************************
     * 初始化接口，android下使用java接口初始化，ios下使用c++接口初始化
     *
     *********************************************************************************/
#ifdef __APPLE__
    static void init (const char* appKey, const char* appChannel=NULL) {logger_init(appKey, appChannel);}
#endif
    
    /*********************************************************************************
     * 事件接口
     *
     *********************************************************************************/
    
    // 关卡启动退出事件，也可以作为页面启动退出事件
    static int  onSubStart (const char* stage) {return logger_onSubStart(stage);}
    static void onSubEnd (const char* stage) {logger_onSubEnd(stage);}
    
    // 过关/失败
    static void onPassFail (bool bPass) {logger_onPassFail(bPass);}

    // 自定义事件
    static void onEvent (const char* name, const char* stage = STAGE_LAST) {logger_onEvent(name, stage);}
    
    // 产出/消耗 平衡数据
    static void onBalance (const char* name, const char* item, int value, const char* stage = STAGE_LAST) {logger_onBalance(name, item, value, stage);}
    
    // 升级事件，可用户账号升级或宠物升级
    static void onLevelUp (const char* name, const char* oldLevel, const char* newLevel, const char* stage = STAGE_LAST) {logger_onLevelUp(name, oldLevel, newLevel, stage);}

    // 购买
    static void onBuy (const char* service, const char* item, int count, float value, const char* stage = STAGE_LAST) {logger_onBuy(service, item, count, value, stage);}
    
    //道具使用
    static void onUse (const char* item, int count, const char* stage = STAGE_LAST) {logger_onUse(item, count, stage);}

    // 赠与/交易：玩家之间
    static void onExchange (const char* item, int count, const char* stage = STAGE_LAST) {logger_onExchange(item, count, stage);}

    // 掉落/收集：游戏进行中获得
    static void onCollect (const char* item, int count, const char* stage = STAGE_LAST) {logger_onCollect(item, count, stage);}

    // 奖励：官方活动
    static void onReward (const char* item, int count, const char* stage = STAGE_LAST) {logger_onReward(item, count, stage);}

    // 分享
    static void onShare(const char* service, const char* item, const char* stage = STAGE_LAST) {logger_onShare(service, item, stage);}
    
    /*********************************************************************************
     * 状态接口
     *
     *********************************************************************************/

    // 状态更新
    static void clearStatus() {logger_clearStatus();}
    static void setStatus(const char* key, int value, bool bAutoConvert = true) {logger_setStatus(key, value, bAutoConvert);}

    /*********************************************************************************
     * 角色接口
     *
     *********************************************************************************/
    static void setUser (const char* level, int age = -1, const char* gender = NULL, const char* userId = NULL, const char* userService = NULL) {logger_setUser(level, age, gender, userId, userService);}
};

#endif //_APPLOGGER_H_