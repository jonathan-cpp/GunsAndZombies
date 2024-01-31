namespace Server
{
    enum PacketType
    {
        BroadcastMessage,	
		PlayerSpawn,
		PlayerConnect,
		PlayerDisconnect,
    };
}

namespace Client
{
    enum PacketType
    {
        PlayerEvent,
        Connect,
        Disconnect,
    };
}