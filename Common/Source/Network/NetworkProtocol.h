namespace NetworkProtocol
{
    enum class PacketType
    {
        // Requests from a client to the server
        Server_GetStatus,
        Server_GetPing,

        // Client-side actions
        Client_Accepted,
        Client_AssignID,
        Client_RegisterWithServer,
        Client_UnregisterWithServer,

        // Server and clients related actions
        Game_AddPlayer,
        Game_RemovePlayer,
        Game_UpdatePlayer,
    };
}