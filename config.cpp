#include "config.h"

config::config() {}

void config::load_settings(params *s)
{
    try
    {
        cfg.readFile("app.cfg");
    }
    catch(const libconfig::FileIOException &fioex)
    {
        qDebug() << "I/O error while reading file.";
        exit(1);
    }
    catch(const libconfig::ParseException &pex)
    {
        qDebug() << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError();
        exit(1);
    }

    const libconfig::Setting& root = cfg.getRoot();

    const libconfig::Setting &params = root["logger"];
    std::string call, file, cat, serial, mode;
    int rig;

    params.lookupValue("callsign", call);
    params.lookupValue("dbfile", file);
    params.lookupValue("category", cat);
    params.lookupValue("mode", mode);
    params.lookupValue("rig", rig);
    params.lookupValue("serial", serial);

    qDebug() << "callsign" << QString::fromUtf8(call.c_str())
         <<  left << "dbfile" << QString::fromUtf8(file.c_str())
         <<  left << "category" << QString::fromUtf8(cat.c_str())
         <<  left << "mode" << QString::fromUtf8(mode.c_str())
         <<  left << "rig" << rig
         <<  left << "serial" << QString::fromUtf8(serial.c_str())
         << endl;

    s->callsign = QString::fromUtf8(call.c_str());
    s->dbfile = QString::fromUtf8(file.c_str());
    s->category = QString::fromUtf8(cat.c_str());
    s->mode = QString::fromUtf8(mode.c_str());
    s->rig = rig;
    s->serial = QString::fromUtf8(serial.c_str());
}

int config::save_settings(QString callsign, QString dbfile, QString category, QString mode, int rig, QString serial)
{
    static const char *output_file = "app.cfg";
    libconfig::Config cfg;

    libconfig::Setting &root = cfg.getRoot();

    // Add some settings to the configuration.
    libconfig::Setting &name = root.add("logger", libconfig::Setting::TypeGroup);

    name.add("callsign", libconfig::Setting::TypeString) = callsign.toStdString().c_str();
    name.add("dbfile", libconfig::Setting::TypeString) = dbfile.toStdString().c_str();
    name.add("category", libconfig::Setting::TypeString) = category.toStdString().c_str();
    name.add("mode", libconfig::Setting::TypeString) = mode.toStdString().c_str();
    name.add("rig", libconfig::Setting::TypeInt) = rig;
    name.add("serial", libconfig::Setting::TypeString) = serial.toStdString().c_str();

    // Write out the new configuration.
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
