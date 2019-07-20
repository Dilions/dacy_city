//+------------------------------------------------------------------+
//|                                            MetaTrader Server API |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "sync.h"
//+------------------------------------------------------------------+
//| Constants                                                        |
//+------------------------------------------------------------------+
#define FILTER_TIME   (5)         // filter parameter (secs)
#define FILTER_COUNT  (2)         // last ticks       (count)
#define VOLUME_DIV    (100.0)     // volume multiplier
//+------------------------------------------------------------------+
//| Global variables                                                 |
//+------------------------------------------------------------------+
PluginInfo          ExtPluginInfo={ "IE Interceptor",101,"MetaQuotes Software Corp.",{0} };
CSync               ExtSync;                       // for future use (synchronization)
CServerInterface   *ExtServer=NULL;                // link to server
//+------------------------------------------------------------------+
//| Command description                                              |
//+------------------------------------------------------------------+
LPCSTR GetCmd(const int cmd)
  {
   static LPCSTR ExtOperations[9]={ "buy","sell","buy limit","sell limit",
      "buy stop","sell stop","balance","credit","error" };
//--- проверки
   if(cmd<OP_BUY || cmd>OP_CREDIT) return(ExtOperations[8]);
//---
   return(ExtOperations[cmd]);
  }
//+------------------------------------------------------------------+
//| DLL entry point                                                  |
//+------------------------------------------------------------------+
BOOL APIENTRY DllMain(HANDLE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
  {
//---
   switch(ul_reason_for_call)
     {
      case DLL_PROCESS_ATTACH:
         break;
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
         break;
      case DLL_PROCESS_DETACH:
         break;
     }
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//| About, must be present always!                                   |
//+------------------------------------------------------------------+
void APIENTRY MtSrvAbout(PluginInfo *info)
  {
   if(info!=NULL) memcpy(info,&ExtPluginInfo,sizeof(PluginInfo));
  }
//+------------------------------------------------------------------+
//| Set server interface point                                       |
//+------------------------------------------------------------------+
int APIENTRY MtSrvStartup(CServerInterface *server)
  {
//--- check version
   if(server==NULL)                        return(FALSE);
   if(server->Version()!=ServerApiVersion) return(FALSE);
//--- save server interface link
   ExtServer=server;
   ExtServer->LogsOut(CmdOK,"IEInterceptor","initialized");
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//| Trade transactions hook                                          |
//+------------------------------------------------------------------+
int APIENTRY MtSrvTradeTransaction(TradeTransInfo *trans,const UserInfo *user,int *request_id)
  {
   int         total;
   char        msg[512];
   TickAPI     ticks[65]={0};
   RequestInfo requote={0};
   time_t      stop_time;
//--- check
   if(trans==NULL || user==NULL || request_id==NULL)                   return(RET_ERROR);
//--- is this instant execution?
   if(trans->type!=TT_ORDER_IE_OPEN && trans->type!=TT_ORDER_IE_CLOSE) return(RET_OK);
//--- query last prices
   if((total=ExtServer->HistoryLastTicks(trans->symbol,ticks,64))<1)   return(RET_OK);
//--- analyze prices
   stop_time=ExtServer->TradeTime()-FILTER_TIME;
   total=min(FILTER_COUNT,total);
   for(int i=0;i<total;i++)
     {
      //--- lets check prices
      if(trans->type==TT_ORDER_IE_OPEN)
        {
         if((trans->cmd==OP_BUY  && trans->price==ticks[i].ask) ||
            (trans->cmd==OP_SELL && trans->price==ticks[i].bid)) return(RET_OK);
        }
      if(trans->type==TT_ORDER_IE_CLOSE)
        {
         if((trans->cmd==OP_BUY  && trans->price==ticks[i].bid) ||
            (trans->cmd==OP_SELL && trans->price==ticks[i].ask)) return(RET_OK);
        }
      //--- check timeout
      if(ticks[i].ctm<stop_time) break; // too old
     }
//--- add record to log
   _snprintf(msg,sizeof(msg)-1,"'%d': instant order %s %.2lf %s at %.5lf sl: %.5lf tp: %.5lf (%.5lf / %.5lf) requoted by IEInterceptor",
                            user->login,GetCmd(trans->cmd),trans->volume/VOLUME_DIV,trans->symbol,trans->price,
                            trans->sl,trans->tp,ticks[0].bid,ticks[0].ask);
   ExtServer->LogsOut(CmdOK,user->ip,msg);
//--- fill request structure for requote
   requote.login       =user->login;
   strcpy(requote.group,user->group);
   requote.balance     =user->balance;
   requote.credit      =user->credit;
   requote.trade.type  =TT_PRICES_REQUOTE;
   requote.trade.volume=trans->volume;
   strcpy(requote.trade.symbol,trans->symbol);
   if(ExtServer->HistoryPrices(trans->symbol,requote.prices,NULL,NULL)!=RET_OK) return(RET_ERROR);
//--- поставим add requote to request queue
   return ExtServer->RequestsAdd(&requote,FALSE,request_id);
  }
//+------------------------------------------------------------------+
