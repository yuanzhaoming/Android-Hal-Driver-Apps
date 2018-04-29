package android.os;

/** {@hide} */
interface ILedService
{
    int ledctl(int which,int state);
}
