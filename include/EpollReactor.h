#pragma once

#include <sys/epoll.h> 
#include <vector>
#include <cstdint>


class EpollReactor{
    private:
    int epoll_fd;
    std::vector<struct epoll_event> events_buffer;

    public:
    explicit EpollReactor(size_t max_events = 64);
    ~EpollReactor();

    EpollReactor(const EpollReactor&) = delete;
    EpollReactor operator=(const EpollReactor&) = delete;

    void add(int fd, uint32_t events);
    void modify(int fd, uint32_t events);
    void remove(int fd);

    
    int wait(int timeout_ms = -1);

    
    const struct epoll_event& get_event(int index) const;
};
