#ifndef LIBRARIES_HPP
# define LIBRARIES_HPP

# include <string>
# include <vector>
# include <map>
# include <poll.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdexcept>
# include <iostream>
# include <cstring>
# include <sstream>
# include <unistd.h>
# include <fcntl.h>
# include <cerrno>
# include <set>
# include <algorithm>
# include <csignal>
# include <cstdlib>

std::vector<std::string> split(const std::string &str, char delimiter);

#endif