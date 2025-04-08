/**
 * @class bot_engine
 * @brief one session per engine, handles message processing
 */
class bot_engine
{
private:
public:
    bot_engine(/* args */);
    ~bot_engine();
    std::string process_message(std::string message, std::string user_id);
};
