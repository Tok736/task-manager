//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_

#include "entity/Entity.h"
#include "database/connection/DbConnector.h"

/**
 * @tparam Connection - тип подключения в зависимости от БД, например, для PostgreSql будет PGconn
 * @tparam ResultSet - тип возвращаемого значения после выполнения запроса, например, для PostgreSql будет PGresult
 */
template<typename Connection, typename ResultSet>
class DbCommand : public Entity {
 private:
  DbConnector<Connection, ResultSet> &_dbConnector;
  std::shared_ptr<Entity> _backUp;

 public:
  explicit DbCommand(const DbConnector<Connection, ResultSet> &) = default;
  DbCommand(const DbCommand<Connection, ResultSet>&) = default;

  std::string toString() const override;

  virtual std::shared_ptr<Entity> getBackUp() const;
  virtual void saveBackUp() = 0;
  virtual void undo() const = 0;
  virtual void execute() const = 0;

  bool operator==(const DbCommand &rhs) const = default;

  ~DbCommand() override = default;
};

template<typename Connection, typename ResultSet>
std::shared_ptr<Entity> DbCommand<Connection, ResultSet>::getBackUp() const {
  return _backUp;
}

template<typename Connection, typename ResultSet>
std::string DbCommand<Connection, ResultSet>::toString() const {
  return "DbCommand backUp: " + _backUp->toString();
}

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCOMMAND_H_
