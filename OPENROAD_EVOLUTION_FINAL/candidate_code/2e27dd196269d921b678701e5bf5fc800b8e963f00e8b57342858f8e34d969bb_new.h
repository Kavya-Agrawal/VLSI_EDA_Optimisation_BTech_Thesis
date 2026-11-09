// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21398699;
  double density_weight = 0.13182662;
  double prefix_weight = 0.11831021;
  double neighborhood_weight = 0.21647013;
  double late_weight = 0.00127079;
  double critical_weight = 0.40333419;
  unsigned budget = 4;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
