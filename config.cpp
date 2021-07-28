#include "config.h"

config::config() {}

config::~config() {}

void config::load_settings(params *s, comcfg *cc, QString& plik_konf)
{
    try
    {
        cfg.readFile(plik_konf.toStdString().c_str());
        qDebug() << "Wczytano";
    }
    catch(const libconfig::FileIOException &fioex)
    {
        qDebug() << "Nie mogę znaleźć pliku konfiguracji";
    }
    catch(const libconfig::ParseException &pex)
    {
        qDebug() << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError();
    }

    const libconfig::Setting& root = cfg.getRoot();

    const libconfig::Setting &params = root["logger"];
    const libconfig::Setting &conn = root["com"];

    std::string call, file, serial, mode, station, power,
            contest, assisted, band, operators, signal,
            soaxp, time, overlay, addres, email, klub,
            baudrate_speed, databits_val, stopbit_val, parity_val, handshake_val;
    int rig;

    params.lookupValue("callsign", call);
    params.lookupValue("dbfile", file);
    params.lookupValue("category-mode", mode);
    params.lookupValue("rig", rig);
    params.lookupValue("serial", serial);
    params.lookupValue("category-station", station);
    params.lookupValue("category-power", power);
    params.lookupValue("contest", contest);
    params.lookupValue("category-assisted", assisted);
    params.lookupValue("category-band", band);
    params.lookupValue("category-operators", operators);
    params.lookupValue("category-signal", signal);
    params.lookupValue("category-soapbox", soaxp);
    params.lookupValue("category-time", time);
    params.lookupValue("category-overlay", overlay);
    params.lookupValue("address", addres);
    params.lookupValue("email", email);
    params.lookupValue("klub", klub);

    conn.lookupValue("baudrate", baudrate_speed);
    conn.lookupValue("databits", databits_val);
    conn.lookupValue("stopbit", stopbit_val);
    conn.lookupValue("parity", parity_val);
    conn.lookupValue("handshake", handshake_val);

    s->callsign = QString::fromUtf8(call.c_str());
    s->dbfile = QString::fromUtf8(file.c_str());
    s->cat_mode = QString::fromUtf8(mode.c_str());
    s->rig = rig;
    s->serial = QString::fromUtf8(serial.c_str());
    s->cat_station = QString::fromUtf8(station.c_str());
    s->cat_power = QString::fromUtf8(power.c_str());
    s->contest = QString::fromUtf8(contest.c_str());
    s->cat_assisted = QString::fromUtf8(assisted.c_str());
    s->cat_band = QString::fromUtf8(band.c_str());
    s->cat_operators = QString::fromUtf8(operators.c_str());
    s->cat_signal = QString::fromUtf8(signal.c_str());
    s->cat_soapbox = QString::fromUtf8(soaxp.c_str());
    s->cat_time = QString::fromUtf8(time.c_str());
    s->cat_overlay = QString::fromUtf8(overlay.c_str());
    s->adress = QString::fromUtf8(addres.c_str());
    s->email = QString::fromUtf8(email.c_str());
    s->klub = QString::fromUtf8(klub.c_str());

    cc->baudrate = QString::fromUtf8(baudrate_speed.c_str());
    cc->databits = QString::fromUtf8(databits_val.c_str());
    cc->stopbit = QString::fromUtf8(stopbit_val.c_str());
    cc->parity = QString::fromUtf8(parity_val.c_str());
    cc->handshake = QString::fromUtf8(handshake_val.c_str());
}

int config::save_settings(params* p, comcfg *cc)
{
    static const char *output_file = "contest_logger.conf";
    libconfig::Config cfg;

    libconfig::Setting &root = cfg.getRoot();

    // Add some settings to the configuration.
    libconfig::Setting &name = root.add("logger", libconfig::Setting::TypeGroup);
    libconfig::Setting &com = root.add("com", libconfig::Setting::TypeGroup);

    name.add("callsign", libconfig::Setting::TypeString) = p->callsign.toUpper().toStdString().c_str();
    name.add("dbfile", libconfig::Setting::TypeString) = p->dbfile.toStdString().c_str();
    name.add("rig", libconfig::Setting::TypeInt) = p->rig;
    name.add("serial", libconfig::Setting::TypeString) = p->serial.toStdString().c_str();

    name.add("category-station", libconfig::Setting::TypeString) = p->cat_station.toStdString().c_str();
    name.add("category-mode", libconfig::Setting::TypeString) = p->cat_mode.toStdString().c_str();
    name.add("category-power", libconfig::Setting::TypeString) = p->cat_power.toStdString().c_str();
    name.add("contest", libconfig::Setting::TypeString) = p->contest.toStdString().c_str();
    name.add("category-assisted", libconfig::Setting::TypeString) = p->cat_assisted.toStdString().c_str();
    name.add("category-band", libconfig::Setting::TypeString) = p->cat_band.toStdString().c_str();
    name.add("category-operators", libconfig::Setting::TypeString) = p->cat_operators.toStdString().c_str();
    name.add("category-signal", libconfig::Setting::TypeString) = p->cat_signal.toStdString().c_str();
    name.add("category-soapbox", libconfig::Setting::TypeString) = p->cat_soapbox.toStdString().c_str();
    name.add("category-time", libconfig::Setting::TypeString) = p->cat_time.toStdString().c_str();
    name.add("category-overlay", libconfig::Setting::TypeString) = p->cat_overlay.toStdString().c_str();
    name.add("address", libconfig::Setting::TypeString) = p->adress.toStdString().c_str();
    name.add("email", libconfig::Setting::TypeString) = p->email.toStdString().c_str();
    name.add("klub", libconfig::Setting::TypeString) = p->klub.toStdString().c_str();
    name.add("wymiana", libconfig::Setting::TypeBoolean) = p->wymiana;
    name.add("wzor", libconfig::Setting::TypeString) = p->pattern.toStdString().c_str();


    com.add("baudate", libconfig::Setting::TypeString) = cc->baudrate.toStdString().c_str();
    com.add("databits", libconfig::Setting::TypeString) = cc->databits.toStdString().c_str();
    com.add("stopbit", libconfig::Setting::TypeString) = cc->stopbit.toStdString().c_str();
    com.add("parity", libconfig::Setting::TypeString) = cc->parity.toStdString().c_str();
    com.add("handshake", libconfig::Setting::TypeString) = cc->handshake.toStdString().c_str();
    // Write new configuration.
    try
    {
        cfg.writeFile(output_file);
        qDebug() << "New configuration successfully written to: " << output_file;
    }
    catch(const libconfig::FileIOException &fioex)
    {
//         qDebug() << "I/O error while writing file: " << output_file << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void config::reset(params *s, comcfg *cc)
{
    s = new params();
    cc = new comcfg();
    (void)s;
    (void)cc;
}
