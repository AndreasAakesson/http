#include <tcp>
#include <response.hpp>

class ServerResponse : public http::Response {
public:
	ServerResponse(std::shared_ptr<TCP::Connection>);

	void send();
	void send(const std::string&);
	void send_file(const fs::FileSystem::Dirent&);
	void send_file(const std::string& path);
	void send_status(int code);

private:
	std::shared_ptr<TCP::Connection> conn_;
};


ServerResponse::ServerResponse(std::shared_ptr<TCP::Connection> conn) 
	: http::Response(), conn_(conn)
{ 

}

void ServerResponse::send() {
	conn_->write(to_string());
}

void ServerResponse::send(const std::string& body) {
	http::Response::set_body(body);
	send();
}

void ServerResponse::send_file(const fs::FileSystem::Dirent& dirent) {
	disk->fs().read(dirent, 0, dirent.size,
	[this](error_t err, buffer_t buff, uint64_t len) {
		auto written = 0;
		while(written < len) {
			written += conn_->write((const char*)buff.get()+written, len - written)); // TCP: What if buffer is full?
		}
	});
}

void ServerResponse::send_file(const std::string& path) {

}

void ServerResponse::send_status(int code) {
	http::Response::set_status_code(code);
	send();
}
