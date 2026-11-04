// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.65269230;
  double density_weight = 0.32049051;
  double prefix_weight = 0.20026425;
  double neighborhood_weight = 0.26914820;
  double late_weight = 0.13979305;
  double critical_weight = 0.10129688;
  unsigned budget = 37;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
