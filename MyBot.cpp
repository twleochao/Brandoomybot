#include "MyBot.h"
#include <dpp/dpp.h>
#include <stdlib.h>
#include <string>

std::string boyNames[10] = {"brandon", "brandoom", "brandomer", "brandoomer", "ansley", "chenbrandon", "brando", "brandoomy", "brandomy*oner"};
std::string girlNames[10] = { "Olivia", "Emma", "Charlotte", "Amelia", "Ava", "Sophia", "Isabella", "Mia", "Evelyn", "Harper" };
int main()
{
    dpp::cluster bot("MTA4NTA0MTQ1NTM3MTkyMzU0OQ.GK288F.-WOv3ODfRNMx5kuX2iCvInH32DUr4ZII-8P13c");
    bot.on_log(dpp::utility::cout_logger());

    
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
         if (event.command.get_command_name() == "brandon") {
             event.reply("I am cringe");
         }
    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "name") {
            std::string gender = std::get<std::string>(event.get_parameter("gender"));
            if (gender == "boy") {
                event.reply(boyNames[rand() % 10]);
            }
            else {
                event.reply(girlNames[rand() % 10]);
            }
        }
        if (event.command.get_command_name() == "hw") {
            dpp::embed hwEmbed = dpp::embed().
                set_color(dpp::colors::scarlet_red).
                set_title("Homework Page").
                set_url("https://docs.google.com/spreadsheets/u/1/d/1bn99zMyRzNDyOganM75vWBauc3Aur85ewXpumIZe73I/pubhtml?gid=0&range=A1:G32&output=html").
                set_image("https://cdn.discordapp.com/attachments/1085038215460823124/1089789493978083410/wide_brandon.jpg").
                set_description("Go do hw").
                set_author("Brandomerbro", "https://docs.google.com/spreadsheets/u/1/d/1bn99zMyRzNDyOganM75vWBauc3Aur85ewXpumIZe73I/pubhtml?gid=0&range=A1:G32&output=html", "https://cdn.discordapp.com/attachments/1085038215460823124/1089789493978083410/wide_brandon.jpg");
            dpp::message reply = dpp::message("HW TIME");
            reply.add_embed(hwEmbed);
            event.reply(reply);
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("brandon", "is brandon cringe?", bot.me.id));
        }
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("hw", "HW TIME?", bot.me.id));
        }
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand newcommand("name", "boy or girl name?", bot.me.id);
            newcommand.add_option(
                dpp::command_option(dpp::co_string, "gender", "pick a gender", true).
                add_choice(dpp::command_option_choice("boy", std::string("boy"))).
                add_choice(dpp::command_option_choice("girl", std::string("girl")))
            );
            bot.global_command_create(newcommand);
        }
    });
    //start
    bot.start(dpp::st_wait);

    return 0;
}
