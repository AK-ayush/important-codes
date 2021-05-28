#include <iostream>
/*


reversrProxyServer():
    map<id, Request> pending_requests
    map<id, Response> incoming_responses

    Response externalGet(request)->Response:
        id = genId(request);
        pending_request[id] = request
        while(!incoming_responses.count(id)); // waiting
        return incoming_responses[id];

    pair<id, Request> internalGet():
        if(pending_request.size() > 0)
            pair<id, Request> curr =  *pending_request.begin()
            pending_request.erase(pending_request.begin());
            return curr
        return {-1, null}
    

    internalPost(pair<id, Response> response_obj):
        incoming_response[response_obj.first] = response_obj.second



reversrProxyClient(){
    while(true){ // always running
        pair<id, Request> curr  = internalGet()
        while(curr.first == -1){
            // wait time
            curr = internalGet() // from the reverseproxy server
        }

        id = curr.first
        request = curr.second

        if(request.target_ip == "http://ayush/foobar"){
            request.update()
            response = request.getResponss() from the server
            pair<id, Response>  response_obj = {id, response}
            internalPost(response_obj) // to the reverseProxyserve
        } 


        * polling the server( check pending_requests) for any request and waiting... 5Min
            * some request is there, say get() from http://ayush/foobar
            * now it will make the get request to respective internal machine
            and get the response and then send the response back to reverseProxyServer();  // yeild python
    }
}
*/



int main() {
    // you can write to stdout for debugging purposes, e.g.
    std::cout << "This is a debug message" << std::endl;
    std::cout<< "MS: Reverse Proxy Server "<<std::endl;
    return 0;
}
// -----
/*
{

A1 : http://ayush/foobar 
B2 : http://diganta/foobar1
}
reverseProxyServer() : https://reverseproxy/A1... [get/ post]
{
    // reverseProxyClient : 
} 

reversrProxyClient() : 


???? simulte outbound thorugh inbound


*/