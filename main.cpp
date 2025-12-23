#include "Wallet.h"
#include "MerkelMain.h"
#include "AccountManager.h"
#include <iostream>

int main()
{   
    MerkelMain app{AccountManager::login()};
    app.init();
}
