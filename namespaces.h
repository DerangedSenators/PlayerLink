/**
 * @brief Root Namespace for the PlayerLink API
*/
namespace PlayerLink {
	/**
	 * @brief Contains source code which is shared by both PlayerLink Server and PlayerLink Client. Compiles to a static library
	*/
	namespace Core{}
	/**
	 * @brief Shared Library which will be implemented by the server application
	*/
	namespace Server {}
	/**
	 * @brief Shared Library which will be implemented by the client application
	*/
	namespace Client {}
}