#include "config.h"

config::config() {}

void config::load_settings(params *s, QString& plik_konf)
{
    try
    {
        cfg.readFile(plik_konf.toStdString().c_str());
    }
    catch(const libconfig::FileIOException &fioex)
    {
        qDebug() << "Nie mogę znaleźć pliku konfiguracji";
//        exit(1);
    }
    catch(const libconfig::ParseException &pex)
    {
        qDebug() << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError();
//        exit(1);
    }

    const libconfig::Setting& root = cfg.getRoot();

    const libconfig::Setting &params = root["logger"];
    std::string call, file, serial, mode;
    int rig;

    params.lookupValue("callsign", call);
    params.lookupValue("dbfile", file);
    params.lookupValue("category-mode", mode);
    params.lookupValue("rig", rig);
    params.lookupValue("serial", serial);

    qDebug() << "callsign" << QString::fromUtf8(call.c_str())
         <<  left << "dbfile" << QString::fromUtf8(file.c_str())
         <<  left << "category-mode" << QString::fromUtf8(mode.c_str())
         <<  left << "rig" << rig
         <<  left << "serial" << QString::fromUtf8(serial.c_str())
         << endl;

    s->callsign = QString::fromUtf8(call.c_str());
    s->dbfile = QString::fromUtf8(file.c_str());
    s->cat_mode = QString::fromUtf8(mode.c_str());
    s->rig = rig;
    s->serial = QString::fromUtf8(serial.c_str());
}

int config::save_settings(QString callsign, QString dbfile, int rig,
                          QString serial, QString cat_station, QString cat_power,
                          QString cat_mode, QString contest, QString cat_assisted,
                          QString cat_band, QString cat_operators, QString cat_signal,
                          QString cat_soapbox, QString cat_time, QString cat_overlay,
                          QString adress, QString email, QString klub, bool wymiana,
                          QString wzor)
{
    static const char *output_file = "contest_logger.conf";
    libconfig::Config cfg;

    libconfig::Setting &root = cfg.getRoot();

    // Add some settings to the configuration.
    libconfig::Setting &name = root.add("logger", libconfig::Setting::TypeGroup);

    name.add("callsign", libconfig::Setting::TypeString) = callsign.toStdString().c_str();
    name.add("dbfile", libconfig::Setting::TypeString) = dbfile.toStdString().c_str();
    name.add("rig", libconfig::Setting::TypeInt) = rig;
    name.add("serial", libconfig::Setting::TypeString) = serial.toStdString().c_str();

    name.add("category-station", libconfig::Setting::TypeString) = cat_station.toStdString().c_str();
    name.add("categot-mode", libconfig::Setting::TypeString) = cat_mode.toStdString().c_str();
    name.add("category-power", libconfig::Setting::TypeString) = cat_power.toStdString().c_str();
    name.add("contest", libconfig::Setting::TypeString) = contest.toStdString().c_str();
    name.add("category-assisted", libconfig::Setting::TypeString) = cat_assisted.toStdString().c_str();
    name.add("category-band", libconfig::Setting::TypeString) = cat_band.toStdString().c_str();
    name.add("category-operators", libconfig::Setting::TypeString) = cat_operators.toStdString().c_str();
    name.add("category-signal", libconfig::Setting::TypeString) = cat_signal.toStdString().c_str();
    name.add("category-soapbox", libconfig::Setting::TypeString) = cat_soapbox.toStdString().c_str();
    name.add("category-time", libconfig::Setting::TypeString) = cat_time.toStdString().c_str();
    name.add("category-overlay", libconfig::Setting::TypeString) = cat_overlay.toStdString().c_str();
    name.add("address", libconfig::Setting::TypeString) = adress.toStdString().c_str();
    name.add("email", libconfig::Setting::TypeString) = email.toStdString().c_str();
    name.add("klub", libconfig::Setting::TypeString) = klub.toStdString().c_str();
    qDebug() << wymiana;
    qDebug() << wzor;
    name.add("wymiana", libconfig::Setting::TypeBoolean) = wymiana;
    name.add("wzor", libconfig::Setting::TypeString) = wzor.toStdString().c_str();

    // Write new configuration.
    try
    {
        cfg.writeFile(output_file);
        qDebug() << "New configuration successfully written to: " << output_file;
    }
    catch(const libconfig::FileIOException &fioex)
    {
        qDebug() << "I/O error while writing file: " << output_file << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
