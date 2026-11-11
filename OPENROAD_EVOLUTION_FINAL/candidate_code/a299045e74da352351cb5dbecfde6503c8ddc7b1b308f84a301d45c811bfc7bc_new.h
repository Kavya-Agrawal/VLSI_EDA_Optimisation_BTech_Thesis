// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32637702;
  double density_weight = 0.18060715;
  double prefix_weight = 0.12621697;
  double neighborhood_weight = 0.32548079;
  double late_weight = 0.21167836;
  double critical_weight = 0.32463949;
  unsigned budget = 15;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
