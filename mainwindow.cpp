#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ordena(new minhaNamespace::Ordena())
{
    ui->setupUi(this);
    ui->comboBoxPorTipo->setEnabled(false);
    ui->comboBoxPorAlfabeto->setEnabled(false);
    //    ui->tableWidgetGrid->setEnabled(false);
    ui->tableWidgetGrid->verticalHeader()->setVisible(false);
}

MainWindow::~MainWindow()
{
    if(ordena) delete ordena;
    delete ui;
}

void MainWindow::setGrid(minhaNamespace::LLDE<minhaNamespace::Pessoa> pessoa)
{
    QStringList qsl = {"Matricula", "Nome"};

    ui->tableWidgetGrid->setHorizontalHeaderLabels(qsl);

    ui->tableWidgetGrid->clearContents();
    ui->tableWidgetGrid->setRowCount(0);

    for(int i = 0; i < pessoa.getQuantidadeDeElementos(); i++) {
        int linha = ui->tableWidgetGrid->rowCount();
        ui->tableWidgetGrid->insertRow(linha);

        QTableWidgetItem *matricula = 0;
        matricula = new QTableWidgetItem(QString::number(pessoa[i].getMatricula()));
        ui->tableWidgetGrid->setItem(linha, 0, matricula);

        QTableWidgetItem *nome = 0;
        nome = new QTableWidgetItem(pessoa[i].getNome());
        ui->tableWidgetGrid->setItem(linha, 1, nome);
    }
}

void MainWindow::on_actionAbrir_triggered()
{
    try {
        std::ifstream arquivo;

        QString nomeDoArquivo = QFileDialog::getOpenFileName(this, "Abrir arquivo",
                                                             QDir::currentPath(), "Arquivos texto (*.csv *.txt)");

        if(nomeDoArquivo.isEmpty()) throw QString("Arquivo não selecionado.");

        arquivo.open(nomeDoArquivo.toStdString().c_str());

        if(!arquivo.is_open()) throw QString("Erro: arquivo não pode ser aberto.");

        std::string linha = "";

        if(ui->comboBoxPorTipo->currentIndex() == 0) ordena->setPorNome(true);

        //        std::getline(arquivo, linha); // como assim?

        while(!arquivo.eof()) {
            std::getline(arquivo, linha);

            ordena->setLista(ordena->splitPessoa(QString::fromStdString(linha)));
        }

        arquivo.close();

        ui->textEditSaida->setText(ordena->getLista(ordena->ordenarListaPorTipo()));
        setGrid(ordena->ordenarListaPorTipo());

        ui->comboBoxPorTipo->setEnabled(true);
        ui->comboBoxPorAlfabeto->setEnabled(true);
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

void MainWindow::on_actionSalvar_triggered()
{
    try {
        QString texto = ordena->getListaSemFormatacao(ordena->ordenarListaPorTipo());

        if(texto.isEmpty()) throw QString("Arquivo vazio.");

        std::ofstream arquivo;

        QString nomeDoArquivo = QFileDialog::getSaveFileName(this, "Novo arquivo",
                                                             QDir::currentPath(), "Arquivos texto (*.csv *.txt)");

        if(nomeDoArquivo.isEmpty()) throw QString("Arquivo não selecionado.");


        arquivo.open(nomeDoArquivo.toStdString().c_str());

        if(!arquivo.is_open()) throw QString("Erro: arquivo não pode ser criado.");

        arquivo << texto.toStdString().c_str() << std::endl;

        arquivo.close();
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

void MainWindow::on_actionSalvar_como_triggered()
{

}

void MainWindow::on_actionLimpar_triggered()
{
    try {
        ui->textEditSaida->clear();

        ui->comboBoxPorTipo->setEnabled(false);
        ui->comboBoxPorAlfabeto->setEnabled(false);
        ui->tableWidgetGrid->clearContents();
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

/*void MainWindow::on_pushButtonAdicionar_clicked()
{
    try {
        QString texto = ordena->getListaSemFormatacao(ordena->ordenarListaPorTipo());

        if(texto.isEmpty()) throw QString("Arquivo vazio.");

        std::fstream arquivo;

        QString nomeDoArquivo = QFileDialog::getOpenFileName(this, "Novo Arquivo",
                                                             QDir::currentPath(), "Arquivos texto (*.csv *.txt)");

        if(nomeDoArquivo.isEmpty()) throw QString("Arquivo não selecionado.");

        arquivo.open(nomeDoArquivo.toStdString().c_str(), std::ios::out | std::ios::app);

        if(!arquivo.is_open()) throw QString("Erro: arquivo não pode ser criado.");

        arquivo<< "\n" << texto.toStdString().c_str() << std::endl;

        arquivo.close();

        ui->textEditSaida->clear();
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}*/


void MainWindow::on_comboBoxPorTipo_activated(int index)
{
    try {
        ui->textEditSaida->clear();

        (index == 0) ? ordena->setPorNome(true) : ordena->setPorNome(false);

        ui->textEditSaida->setText(ordena->getLista(ordena->ordenarListaPorTipo()));
        setGrid(ordena->ordenarListaPorTipo());
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

void MainWindow::on_comboBoxPorAlfabeto_activated(int index)
{
    try {
        ui->textEditSaida->clear();

        (index == 0) ? ordena->setEDecrescente(false) : ordena->setEDecrescente(true);

        ui->textEditSaida->setText(ordena->getLista(ordena->ordenarListaPorTipo()));
        setGrid(ordena->ordenarListaPorTipo());
    }  catch (QString &erro) {
        QMessageBox::information(this, "Erro", erro);
    }
}

